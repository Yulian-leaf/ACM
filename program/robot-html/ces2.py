import os
import torch
import numpy as np
from flask import Flask, request, jsonify, render_template_string
from transformers import BertForSequenceClassification, BertTokenizer
from torch.nn.functional import softmax
import time
import re
import random

# 初始化Flask应用
app = Flask(__name__)

# ------------------------------
# 情感分析模型 - 本地加载中文模型
# ------------------------------

# 获取当前脚本所在的目录
BASE_DIR = os.path.dirname(os.path.abspath(__file__))

# 模型文件目录 - 使用绝对路径
MODEL_DIR = os.path.join(BASE_DIR, "chinese_sentiment_model")

# 确保模型目录存在
os.makedirs(MODEL_DIR, exist_ok=True)

print(f"当前工作目录: {os.getcwd()}")
print(f"模型目录路径: {MODEL_DIR}")

# 情感类型映射到中文
EMOTION_MAP = {
    'anger': '生气',
    'fear': '害怕',
    'joy': '高兴',
    'love': '喜爱',
    'sadness': '悲伤',
    'surprise': '惊讶',
    'neutral': '中性'
}

# 情感颜色映射
EMOTION_COLORS = {
    'anger': '#ff6b6b',
    'fear': '#9d4edd',
    'joy': '#4ecdc4',
    'love': '#ff6b6b',
    'sadness': '#6a6af5',
    'surprise': '#f9c74f',
    'neutral': '#b0b0b0'
}

# 尝试从本地加载模型
try:
    print(f"正在从本地加载中文情感模型: {MODEL_DIR}")
    
    # 检查模型目录是否存在
    if not os.path.exists(MODEL_DIR):
        raise FileNotFoundError(f"模型目录不存在: {MODEL_DIR}")
    
    # 列出目录中的所有文件
    print(f"模型目录中的文件: {os.listdir(MODEL_DIR)}")
    
    # 检查模型文件是否存在
    required_files = ['config.json', 'pytorch_model.bin', 'vocab.txt']
    missing_files = []
    
    for file in required_files:
        file_path = os.path.join(MODEL_DIR, file)
        if not os.path.exists(file_path):
            missing_files.append(file_path)
            print(f"❌ 文件不存在: {file_path}")
        else:
            print(f"✅ 找到文件: {file_path}")
    
    if missing_files:
        raise FileNotFoundError(f"缺少模型文件: {', '.join(missing_files)}")
    
    # 加载tokenizer
    print("正在加载分词器...")
    tokenizer = BertTokenizer.from_pretrained(MODEL_DIR)
    
    # 加载模型
    print("正在加载模型...")
    model = BertForSequenceClassification.from_pretrained(MODEL_DIR)
    
    # 设置模型为评估模式
    model.eval()
    
    print("✅ 中文情感模型加载成功！")
    
except Exception as e:
    print(f"❌ 模型加载失败: {str(e)}")
    print("请确保：")
    print(f"1. 模型目录 '{MODEL_DIR}' 存在且包含所有必需文件")
    print("2. 文件未损坏")
    print("3. 模型格式正确")
    print("4. 文件路径正确")
    
    # 创建后备模型和分词器
    print("⚠️ 创建后备模型和分词器...")
    tokenizer = BertTokenizer.from_pretrained("bert-base-chinese")
    model = BertForSequenceClassification.from_pretrained("bert-base-chinese", num_labels=6)
    model.eval()
    print("✅ 后备模型加载完成，但功能可能受限")

def analyze_sentiment(text):
    """使用本地加载的中文模型进行情感分析"""
    try:
        # 预处理文本
        text = re.sub(r'[^\w\s]', '', text)  # 去除标点符号
        
        # 准备模型输入
        inputs = tokenizer(
            text,
            padding='max_length',
            truncation=True,
            max_length=128,
            return_tensors="pt"
        )
        
        # 获取模型预测
        with torch.no_grad():
            outputs = model(**inputs)
        
        logits = outputs.logits.detach().cpu().numpy()
        probabilities = softmax(torch.tensor(logits), dim=1).numpy()[0]
        
        # 情感标签列表 (对应模型输出顺序)
        emotion_labels = ['anger', 'fear', 'joy', 'love', 'sadness', 'surprise']
        
        # 获取主要情感和置信度
        primary_idx = np.argmax(probabilities)
        primary_emotion = emotion_labels[primary_idx]
        confidence = float(probabilities[primary_idx])
        
        # 处理低置信度情况
        if confidence < 0.5:
            return 'neutral', max(confidence, 0.3)  # 确保置信度不低于30%
        
        return primary_emotion, confidence
        
    except Exception as e:
        print(f"情感分析错误: {str(e)}")
        return 'neutral', 0.5

# ------------------------------
# 响应生成系统 - 中文版
# ------------------------------

RESPONSE_DATABASE = {
    'anger': [
        "我理解你现在可能很生气，让我们一起冷静下来思考问题",
        "听起来你很愤怒，或许换个角度看事情会不一样",
        "愤怒是正常的情绪，但不要让它们控制你",
        "生气的时候深呼吸几次可能会有所帮助"
    ],
    'fear': [
        "感觉到你有些害怕，但请记住你是安全的",
        "恐惧常常源于未知，我们试着一起了解它好吗？",
        "感到害怕很正常，你正在勇敢地面对它",
        "恐惧并不可怕，正视它才能真正战胜它"
    ],
    'joy': [
        "真为你感到高兴！喜悦的情绪是会传染的！",
        "听到你开心真好！继续保持这份好心情",
        "开心是最好的礼物，感谢你分享这份快乐",
        "你快乐的心情也感染了我！"
    ],
    'love': [
        "感受到你满满的爱意了！",
        "有爱的陪伴真是一件幸福的事情",
        "爱让这个世界更美好，感谢你分享这份情感",
        "爱与被爱是人生最珍贵的礼物"
    ],
    'sadness': [
        "我能感受到你的难过，这种情绪我理解",
        "你并不孤单，我会一直在这里陪你",
        "悲伤是人之常情，给自己时间慢慢恢复",
        "无论有多难过，太阳明天依然会升起"
    ],
    'surprise': [
        "哦？发生什么出人意料的事了吗？",
        "惊喜总是让生活更有趣！",
        "意想不到的事情常常带来新的机遇",
        "能分享下是什么让你这么惊讶吗？"
    ],
    'neutral': [
        "感谢你和我分享这些",
        "我理解你说的内容了",
        "这确实值得思考，我能理解你的想法",
        "你的观点很有意义"
    ]
}

def generate_response(emotion, confidence):
    """根据情感和置信度生成中文响应"""
    try:
        # 根据置信度选择不同层级的回应
        if confidence > 0.8:  # 高置信度
            responses = RESPONSE_DATABASE.get(emotion, RESPONSE_DATABASE['neutral'])
            response = random.choice(responses)
        elif confidence > 0.5:  # 中等置信度
            responses = RESPONSE_DATABASE.get(emotion, RESPONSE_DATABASE['neutral'])
            neutral_responses = RESPONSE_DATABASE['neutral']
            response = random.choice(responses + neutral_responses)
        else:  # 低置信度
            response = random.choice(RESPONSE_DATABASE['neutral'])
            
        return response
        
    except Exception as e:
        print(f"响应生成错误: {str(e)}")
        return "我正在思考如何回应你，请再说详细点好吗？"

# ------------------------------
# API接口
# ------------------------------

@app.route('/chat', methods=['POST'])
def chat_api():
    data = request.get_json()
    if not data or 'message' not in data:
        return jsonify({"error": "请提供消息内容"}), 400
    
    user_message = data['message']
    
    # 分析用户情感
    emotion, confidence = analyze_sentiment(user_message)
    
    # 生成响应
    bot_response = generate_response(emotion, confidence)
    
    return jsonify({
        "user_message": user_message,
        "bot_response": bot_response,
        "detected_emotion": emotion,
        "confidence": confidence
    })

# ------------------------------
# 精美中文界面
# ------------------------------

@app.route('/')
def index():
    return render_template_string("""
    <!DOCTYPE html>
    <html lang="zh-CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>中文情感聊天机器人</title>
        <style>
            * {
                box-sizing: border-box;
                margin: 0;
                padding: 0;
                font-family: 'PingFang SC', 'Microsoft YaHei', sans-serif;
            }
            
            body {
                background-color: #f5f7ff;
                height: 100vh;
                display: flex;
                justify-content: center;
                align-items: center;
                padding: 15px;
            }
            
            .chat-container {
                width: 100%;
                max-width: 500px;
                height: 90vh;
                background-color: white;
                border-radius: 20px;
                box-shadow: 0 10px 30px rgba(125, 130, 242, 0.2);
                display: flex;
                flex-direction: column;
                overflow: hidden;
            }
            
            .chat-header {
                background: linear-gradient(135deg, #6a70e4, #9d83d9);
                color: white;
                padding: 20px;
                text-align: center;
                box-shadow: 0 3px 10px rgba(0,0,0,0.08);
                position: relative;
                z-index: 10;
            }
            
            .chat-header h1 {
                font-size: 22px;
                font-weight: 600;
                letter-spacing: 0.5px;
            }
            
            .chat-header p {
                font-size: 14px;
                opacity: 0.95;
                margin-top: 6px;
            }
            
            .chat-box {
                flex: 1;
                padding: 20px 15px;
                overflow-y: auto;
                background-color: #f9f9ff;
                display: flex;
                flex-direction: column;
            }
            
            .message {
                margin-bottom: 20px;
                max-width: 85%;
                position: relative;
                animation: fadeIn 0.4s ease;
            }
            
            @keyframes fadeIn {
                from { opacity: 0; transform: translateY(15px); }
                to { opacity: 1; transform: translateY(0); }
            }
            
            .bot-message {
                align-self: flex-start;
                background-color: white;
                border-radius: 18px 18px 18px 5px;
                padding: 14px;
                box-shadow: 0 2px 8px rgba(0,0,0,0.05);
                margin-right: 50px;
            }
            
            .user-message {
                align-self: flex-end;
                background: linear-gradient(135deg, #6a70e4, #9d83d9);
                color: white;
                border-radius: 18px 18px 5px 18px;
                padding: 14px;
                margin-left: 50px;
            }
            
            .message-content {
                font-size: 16px;
                line-height: 1.5;
            }
            
            .emoji-btn {
                width: 35px;
                height: 35px;
                border-radius: 50%;
                background: white;
                display: flex;
                align-items: center;
                justify-content: center;
                font-size: 18px;
                cursor: pointer;
                transition: all 0.2s;
                margin: 0 3px;
                box-shadow: 0 2px 5px rgba(0,0,0,0.1);
            }
            
            .emoji-btn:hover {
                transform: scale(1.1);
                background: #f0f0ff;
            }
            
            .timestamp {
                font-size: 12px;
                color: #999;
                text-align: right;
                margin-top: 5px;
            }
            
            .bot-message .timestamp {
                color: #888;
                text-align: left;
            }
            
            .emotion-info {
                margin-top: 8px;
                font-size: 13px;
                color: #666;
                padding: 6px 8px;
                background-color: #f6f7ff;
                border-radius: 10px;
                display: inline-block;
                border: 1px solid #e6e6ff;
            }
            
            .emotion-tag {
                display: inline-block;
                padding: 3px 8px;
                border-radius: 12px;
                font-size: 12px;
                margin-right: 5px;
                font-weight: 500;
            }
            
            .confidence-bar {
                display: inline-block;
                width: 70px;
                height: 6px;
                background: #f0f0f0;
                border-radius: 3px;
                overflow: hidden;
                vertical-align: middle;
                margin-left: 8px;
            }
            
            .confidence-level {
                height: 100%;
                border-radius: 3px;
                transition: width 0.5s;
            }
            
            .emoji-container {
                display: flex;
                justify-content: center;
                padding: 10px 0;
                background-color: white;
                border-top: 1px solid #eee;
            }
            
            .input-area {
                padding: 15px;
                border-top: 1px solid #f0f0f0;
                background-color: white;
                display: flex;
                align-items: center;
            }
            
            #userInput {
                flex: 1;
                padding: 14px 18px;
                border: 1px solid #ddd;
                border-radius: 30px;
                font-size: 16px;
                outline: none;
                transition: border-color 0.3s;
                background-color: #fafaff;
            }
            
            #userInput:focus {
                border-color: #9d83d9;
                box-shadow: 0 0 0 3px rgba(157, 131, 217, 0.2);
            }
            
            #sendBtn {
                background: linear-gradient(135deg, #6a70e4, #9d83d9);
                color: white;
                border: none;
                border-radius: 30px;
                padding: 14px 25px;
                margin-left: 12px;
                cursor: pointer;
                font-weight: 500;
                font-size: 16px;
                box-shadow: 0 4px 12px rgba(106, 112, 228, 0.3);
                transition: all 0.3s;
            }
            
            #sendBtn:hover {
                opacity: 0.95;
                transform: translateY(-2px);
                box-shadow: 0 6px 14px rgba(106, 112, 228, 0.4);
            }
            
            #sendBtn:disabled {
                opacity: 0.7;
                transform: none;
                cursor: not-allowed;
            }
            
            .typing-indicator {
                display: inline-flex;
                padding: 10px 18px;
                background-color: white;
                border-radius: 18px;
                margin: 5px 0 20px;
                box-shadow: 0 2px 8px rgba(0,0,0,0.05);
                align-self: flex-start;
            }
            
            .typing-dot {
                width: 8px;
                height: 8px;
                background-color: #9d83d9;
                border-radius: 50%;
                margin: 0 3px;
                animation: typing 1.4s infinite;
            }
            
            .typing-dot:nth-child(2) { animation-delay: 0.2s; }
            .typing-dot:nth-child(3) { animation-delay: 0.4s; }
            
            @keyframes typing {
                0%, 100% { transform: translateY(0); }
                50% { transform: translateY(-5px); }
            }
            
            .welcome-card {
                background-color: white;
                padding: 20px;
                border-radius: 16px;
                box-shadow: 0 5px 15px rgba(0,0,0,0.05);
                text-align: center;
                margin-bottom: 25px;
                border: 1px solid #f0f0ff;
            }
            
            .welcome-card h3 {
                color: #6a70e4;
                margin-bottom: 15px;
                font-weight: 6
            .welcome-card p {
                color: #666;
                font-size: 15px;
                line-height: 1.6;
                margin-bottom: 15px;
            }
            
            /* 响应式设计 */
            @media (max-width: 500px) {
                .chat-container {
                    height: 95vh;
                    border-radius: 16px;
                }
                
                .chat-header {
                    padding: 15px 10px;
                }
                
                .chat-header h1 {
                    font-size: 20px;
                }
                
                .message {
                    max-width: 90%;
                }
                
                .input-area {
                    padding: 12px;
                }
                
                #userInput {
                    padding: 12px 15px;
                    font-size: 15px;
                }
                
                #sendBtn {
                    padding: 12px 18px;
                    font-size: 15px;
                }
                
                .welcome-card {
                    padding: 15px;
                }
            }
        </style>
    </head>
    <body>
        <div class="chat-container">
            <div class="chat-header">
                <h1>中文情感聊天机器人</h1>
                <p>我能理解你的感受并做出有同理心的回应</p>
            </div>
            
            <div class="chat-box" id="chatBox">
                <div class="welcome-card">
                    <h3>👋 欢迎使用中文情感聊天机器人</h3>
                    <p>我是基于本地中文模型的情感智能助手，擅长理解中文情感表达。你可以自由表达心情感受，我会尽力理解并给予支持。</p>
                    <p><strong>本地中文情感识别</strong> | 完全离线运行 | 情感置信度精准分析</p>
                </div>
                
                <div class="message">
                    <div class="bot-message">
                        <div class="message-content">你好！我是中文情感聊天机器人，可以随时和我分享你的心情～</div>
                        <div class="timestamp">22:13</div>
                    </div>
                </div>
            </div>
            
            <div class="emoji-container">
                <div class="emoji-btn" data-emoji="😂">😂</div>
                <div class="emoji-btn" data-emoji="😭">😭</div>
                <div class="emoji-btn" data-emoji="😠">😠</div>
                <div class="emoji-btn" data-emoji="😨">😨</div>
                <div class="emoji-btn" data-emoji="😍">😍</div>
            </div>
            
            <div class="input-area">
                <input type="text" id="userInput" placeholder="输入你的消息..." autocomplete="off">
                <button id="sendBtn">发送</button>
            </div>
        </div>
        
        <script>
            // 情感颜色映射
            const emotionColors = {
                'anger': '#ff6b6b',
                'fear': '#9d4edd',
                'joy': '#4ecdc4',
                'love': '#ff6b6b',
                'sadness': '#6a6af5',
                'surprise': '#f9c74f',
                'neutral': '#b0b0b0'
            };
            
            // 情感中文映射
            const emotionChinese = {
                'anger': '生气',
                'fear': '害怕',
                'joy': '高兴',
                'love': '喜爱',
                'sadness': '悲伤',
                'surprise': '惊讶',
                'neutral': '中性'
            };
            
            // 获取当前时间格式
            function getCurrentTime() {
                const now = new Date();
                const hours = now.getHours().toString().padStart(2, '0');
                const minutes = now.getMinutes().toString().padStart(2, '0');
                return `${hours}:${minutes}`;
            }
            
            // 添加消息到聊天框
            function addMessage(content, isUser = false, emotionInfo = null) {
                const chatBox = document.getElementById('chatBox');
                const timestamp = getCurrentTime();
                
                const messageDiv = document.createElement('div');
                messageDiv.className = 'message';
                
                if (isUser) {
                    messageDiv.innerHTML = `
                        <div class="user-message">
                            <div class="message-content">${content}</div>
                            <div class="timestamp">${timestamp}</div>
                        </div>
                    `;
                } else {
                    let emotionDisplay = '';
                    
                    if (emotionInfo) {
                        const emotionColor = emotionColors[emotionInfo.emotion] || '#b0b0b0';
                        const emotionName = emotionChinese[emotionInfo.emotion] || '中性';
                        const confidencePercent = Math.round(emotionInfo.confidence * 100);
                        
                        emotionDisplay = `
                            <div class="emotion-info">
                                <span class="emotion-tag" style="background-color:${emotionColor}20;color:${emotionColor}">
                                    ${emotionName}
                                </span>
                                <span>置信度: ${confidencePercent}%</span>
                                <div class="confidence-bar">
                                    <div class="confidence-level" style="width:${confidencePercent}%;background-color:${emotionColor}"></div>
                                </div>
                            </div>
                        `;
                    }
                    
                    messageDiv.innerHTML = `
                        <div class="bot-message">
                            <div class="message-content">${content}</div>
                            <div class="timestamp">${timestamp}</div>
                            ${emotionDisplay}
                        </div>
                    `;
                }
                
                chatBox.appendChild(messageDiv);
                scrollToBottom();
            }
            
            // 显示正在输入状态
            function showTypingIndicator() {
                const chatBox = document.getElementById('chatBox');
                const typingDiv = document.createElement('div');
                typingDiv.className = 'message';
                
                typingDiv.innerHTML = `
                    <div class="typing-indicator">
                        <div class="typing-dot"></div>
                        <div class="typing-dot"></div>
                        <div class="typing-dot"></div>
                    </div>
                `;
                
                typingDiv.id = 'typingIndicator';
                chatBox.appendChild(typingDiv);
                scrollToBottom();
            }
            
            // 移除正在输入状态
            function removeTypingIndicator() {
                const typingDiv = document.getElementById('typingIndicator');
                if (typingDiv) {
                    typingDiv.remove();
                }
            }
            
            // 滚动到底部
            function scrollToBottom() {
                const chatBox = document.getElementById('chatBox');
                chatBox.scrollTop = chatBox.scrollHeight;
            }
            
            // 发送消息到服务器
            async function sendMessage() {
                const userInput = document.getElementById('userInput');
                const sendBtn = document.getElementById('sendBtn');
                const message = userInput.value.trim();
                
                if (!message) return;
                
                // 禁用按钮防止多次点击
                sendBtn.disabled = true;
                
                // 添加用户消息
                addMessage(message, true);
                userInput.value = '';
                
                // 显示正在输入
                showTypingIndicator();
                
                try {
                    // 发送请求到后端API
                    const response = await fetch('/chat', {
                        method: 'POST',
                        headers: {
                            'Content-Type': 'application/json'
                        },
                        body: JSON.stringify({ message: message })
                    });
                    
                    if (!response.ok) {
                        throw new Error('请求失败');
                    }
                    
                    const data = await response.json();
                    removeTypingIndicator();
                    
                    // 添加机器人响应
                    addMessage(data.bot_response, false, {
                        emotion: data.detected_emotion,
                        confidence: data.confidence
                    });
                    
                } catch (error) {
                    console.error('发送消息失败:', error);
                    removeTypingIndicator();
                    addMessage('抱歉，暂时无法处理你的请求，请稍后再试', false);
                } finally {
                    sendBtn.disabled = false;
                    userInput.focus();
                }
            }
            
            // 初始化事件监听
            document.addEventListener('DOMContentLoaded', function() {
                const sendBtn = document.getElementById('sendBtn');
                const userInput = document.getElementById('userInput');
                
                // 发送按钮事件
                sendBtn.addEventListener('click', function() {
                    const content = userInput.value.trim();
                    if (content) {
                        sendMessage();
                    }
                });
                
                // 输入框回车事件
                userInput.addEventListener('keypress', function(e) {
                    if (e.key === 'Enter') {
                        const content = userInput.value.trim();
                        if (content) {
                            sendMessage();
                        }
                    }
                });
                
                // 表情按钮事件
                document.querySelectorAll('.emoji-btn').forEach(btn => {
                    btn.addEventListener('click', function() {
                        userInput.value += this.dataset.emoji;
                        userInput.focus();
                    });
                });
                
                // 初始滚动到底部
                scrollToBottom();
                userInput.focus();
            });
        </script>
    </body>
    </html>
    """)

# 主程序
if __name__ == '__main__':
    print("中文情感聊天机器人服务启动...")
    print(f"模型目录: {os.path.abspath(MODEL_DIR)}")
    print("访问 http://localhost:5000 开始聊天")
    app.run(host='0.0.0.0', port=5000, debug=True)