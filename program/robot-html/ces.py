# emotion_chatbot_enhanced.py
"""
情感聊天机器人 - 增强版
针对准确性问题和界面显示问题进行优化
"""

from flask import Flask, request, jsonify, render_template_string
import random
import re
import time
import logging
import emoji

# 设置日志
logging.basicConfig(level=logging.INFO)
logger = logging.getLogger("EnhancedEmotionBot")

app = Flask(__name__)

# ------------------------------
# 增强版情感分析引擎
# ------------------------------

# 情感关键词映射 - 增强版
EMOTION_KEYWORDS = {
    'joy': ['高兴', '开心', '快乐', '喜悦', '兴奋', '欣喜', '愉快', '幸福', '哈哈', '呵呵', '嘻嘻', '爱你', 
            '喜欢', '大笑', '棒极了', '太好了', '完美', '棒棒哒', '超赞', '精彩', '优秀', '欢乐', '痛快', '甜蜜'],
    'sadness': ['伤心', '难过', '悲伤', '哭泣', '眼泪', '失落', '忧郁', '沮丧', '痛苦', '伤感', '心碎', '心疼', 
                '绝望', '孤单', '难受', '想哭', '委屈', '煎熬', '失恋', '崩溃', '无奈', '失去', '抑郁'],
    'anger': ['生气', '愤怒', '发火', '恼火', '怒气', '气愤', '愤慨', '暴怒', '不爽', '气死', '发飙', '怒火', 
              '愤怒', '气人', '烦躁', '讨厌', '恨死', '可恶', '烦死了', '怒', '气炸', '气疯', '抓狂'],
    'fear': ['害怕', '恐惧', '担心', '惊慌', '恐慌', '不安', '焦虑', '紧张', '担忧', '恐慌', '发慌', '惧怕', 
             '恐怖', '惊吓', '怕死', '不安', '提心吊胆', '心慌', '心惊', '吓人', '恐'],
    'surprise': ['惊讶', '惊喜', '惊奇', '吃惊', '意外', '诧异', '没想到', '吓一跳', '震惊', '哇塞', '哇哦', 
                 '竟然', '意想不到', '不可思议', '居然', '出乎意料', '惊艳', '惊呆'],
    'love': ['爱', '喜欢', '恋爱', '心动', '亲爱的', '痴情', '迷恋', '钟情', '爱心', '情人', '宝贝', '老婆', 
             '老公', '甜心', '亲爱的', '想你', '恋人', '爱慕', '倾心']
}

# 情感强度增强词
INTENSITY_BOOSTERS = {
    '非常': 1.3, '特别': 1.3, '超级': 1.2, '极其': 1.4, '十分': 1.2,
    '太': 1.2, '极为': 1.4, '格外': 1.2, '极度': 1.4, '超': 1.2,
    '异常': 1.3, '无比': 1.4, '有点': 0.8, '些许': 0.8, '稍微': 0.7
}

# 常用表达模式增强
COMMON_PATTERNS = {
    'joy': [
        r'开心(得|到|死|极了|坏了)', 
        r'高兴(得|到|死|极了|坏了)',
        r'笑了(半天|不停|出声|岔气)',
        r'(哈哈)+',
        r'好(开心|高兴|快乐)',
        r'棒(极了|呆了)'
    ],
    'sadness': [
        r'心(都|碎|痛|疼)了',
        r'难(过|受|熬)得(很|要命)',
        r'想哭(一场|很久)',
        r'泪(流满面|如雨下)',
        r'好(难过|伤心|痛苦)'
    ],
    'anger': [
        r'气(死|炸|疯|得)(我|死|人|要命)',
        r'(忍|受|接|憋)不(住|了|下去)',
        r'太(生气|愤怒)了'
    ]
}

# 情感短语增强映射
PHRASE_MAPPING = {
    '哇塞': ('surprise', 0.95),
    '太棒了': ('joy', 0.92),
    '气死我了': ('anger', 0.94),
    '吓死我了': ('fear', 0.93),
    '想你了': ('love', 0.90),
    '好难过': ('sadness', 0.91),
    '真开心': ('joy', 0.92),
    '太开心了': ('joy', 0.93),
    '好生气': ('anger', 0.92),
    '好害怕': ('fear', 0.91),
    '好惊喜': ('surprise', 0.92),
    '好喜欢': ('love', 0.90),
    '哈哈哈': ('joy', 0.92),
    '呜呜呜': ('sadness', 0.92)
}

def analyze_sentiment(text):
    """增强版情感分析引擎 - 大幅提升准确性和置信度"""
    original_text = text
    text = text.lower()
    
    # 1. 检查常见情感短语
    for phrase, (emotion, confidence) in PHRASE_MAPPING.items():
        if phrase in text:
            return emotion, confidence
    
    # 2. 增强模式匹配
    for emotion, patterns in COMMON_PATTERNS.items():
        for pattern in patterns:
            if re.search(pattern, text):
                return emotion, 0.90
    
    # 3. 情感关键词检测
    emotion_scores = {}
    for emotion, keywords in EMOTION_KEYWORDS.items():
        score = 0
        for keyword in keywords:
            if keyword in text:
                # 检查强度增强词
                for booster, intensity in INTENSITY_BOOSTERS.items():
                    if booster + keyword in text:
                        score += 1 * intensity
                        break
                else:
                    score += 1
        if score > 0:
            emotion_scores[emotion] = score
    
    if emotion_scores:
        # 找到最高分的情感
        max_emotion = max(emotion_scores, key=emotion_scores.get)
        max_score = emotion_scores[max_emotion]
        
        # 计算置信度
        confidence = min(0.95, max_score * 0.3)
        
        # 多个关键词增强置信度
        if emotion_scores[max_emotion] > 1:
            confidence = min(0.98, confidence + 0.15)
            
        return max_emotion, confidence
    
    # 4. 表情符号检测
    if any(char in emoji.UNICODE_EMOJI['en'] for char in original_text):
        for char in original_text:
            if char in emoji.UNICODE_EMOJI['en']:
                emoji_text = emoji.demojize(char).strip(':')
                if 'face_with_tears' in emoji_text:
                    return 'joy', 0.92
                elif 'crying_face' in emoji_text or 'sad_face' in emoji_text:
                    return 'sadness', 0.91
                elif 'angry_face' in emoji_text:
                    return 'anger', 0.91
                elif 'fearful_face' in emoji_text:
                    return 'fear', 0.90
                elif 'heart' in emoji_text:
                    return 'love', 0.93
                elif 'surprised_face' in emoji_text:
                    return 'surprise', 0.90
                elif 'smil' in emoji_text or 'happy' in emoji_text:
                    return 'joy', 0.90
        return 'neutral', 0.70
    
    # 5. 文本长度分析
    if len(text) > 20:
        return 'neutral', 0.75
    return 'neutral', 0.65

# 增强情感响应策略
RESPONSE_STRATEGIES = {
    'joy': [
        "真为你高兴！开心的时光最值得珍惜！",
        "感受到你的喜悦了！快乐是会传染的！",
        "分享快乐会让生活更美好，谢谢你分享！",
        "看到你开心，我也忍不住笑了！",
        "快乐的时刻就是人生的小确幸！保持这份心情！"
    ],
    'sadness': [
        "我感受到你有些难过，这种情绪是自然的",
        "每个人都会经历低潮期，这不是你的错",
        "难过的时候让心情自然流淌，不用压抑",
        "经历低谷才能更好地感受高峰，我在听你说",
        "你的感受很重要，说出来会舒服一些"
    ],
    'love': [
        "爱让世界更温暖！感受爱的力量是美好的",
        "能感受到爱与被爱，是人生中最珍贵的礼物",
        "真挚的爱值得好好珍惜和守护",
        "心中有爱的人眼中都有光芒",
        "爱让我们更勇敢也更温柔"
    ],
    'anger': [
        "听起来你有些生气，让我们一起冷静思考",
        "我理解你的愤怒情绪，能聊聊原因吗？",
        "生气时深呼吸三次，通常会有帮助",
        "找到愤怒的根源往往是解决问题的开始",
        "情绪像天气，愤怒的云会散去的"
    ],
    'fear': [
        "感到害怕很正常，面对恐惧是勇气的开始",
        "恐惧往往是想象的产物，真实并没有那么可怕",
        "深呼吸，你比想象中更强大",
        "面对恐惧最好的方法就是了解它",
        "每个人都会害怕，你并不孤单"
    ],
    'surprise': [
        "哦？发生什么特别的事情了吗？",
        "意外有时带来惊喜，有时带来转折",
        "惊喜就像生活送给我们的神秘礼物",
        "意想不到的事情往往最有故事",
        "被惊喜到的那一刻最难忘"
    ],
    'gratitude': [
        "很高兴能帮到你！",
        "能帮到你真是太好了",
        "很荣幸能为你提供帮助",
        "随时愿意为你效劳"
    ],
    'greeting': [
        "你好呀！今天心情怎么样？",
        "很高兴见到你，有什么想分享的吗？",
        "嗨！今天过得如何？",
        "你好！我是你的情感伙伴"
    ],
    'farewell': [
        "再见，期待下次交流！",
        "保持联系，祝你一切顺利！",
        "下次聊，保持好心情！",
        "晚安，做个好梦！"
    ],
    'neutral': [
        "感谢你愿意和我分享这些",
        "我理解你的意思了，继续说吧",
        "这是一个值得思考的观点",
        "每个人都有自己的看法，你的想法很重要",
        "这让我想到了更多可能性"
    ]
}

DEFAULT_RESPONSES = [
    "谢谢你的分享",
    "我理解你的感受",
    "这是个值得探讨的话题",
    "你的想法很有价值",
    "每个人都有自己的视角"
]

# 情感响应生成器
def generate_response(text):
    try:
        emotion, confidence = analyze_sentiment(text)
        logger.info(f"情感分析结果: {emotion} (置信度: {confidence:.2f})")
        
        # 模拟思考时间
        time.sleep(min(0.8, max(0.3, 1 - confidence)))
        
        # 获取响应
        if emotion in RESPONSE_STRATEGIES:
            # 对特定情感增强响应
            if emotion == 'sadness' and confidence > 0.7:
                responses = RESPONSE_STRATEGIES['sadness'] + [
                    "如果你愿意，可以多说些，我在这里倾听",
                    "需要聊聊发生了什么吗？我在这里陪着你"
                ]
            elif emotion == 'joy' and confidence > 0.8:
                responses = RESPONSE_STRATEGIES['joy'] + [
                    "能分享这么开心的事真棒！",
                    "快乐的能量感染了我！"
                ]
            else:
                responses = RESPONSE_STRATEGIES[emotion]
                
            response = random.choice(responses)
        else:
            response = random.choice(DEFAULT_RESPONSES)
            
        return response, emotion, confidence
    
    except Exception as e:
        logger.error(f"生成响应失败: {str(e)}")
        return "我正在思考如何回应...", "error", 0.0

# ------------------------------
# API接口
# ------------------------------
@app.route('/chat', methods=['POST'])
def chat_api():
    data = request.get_json()
    if not data or 'message' not in data:
        return jsonify({"error": "请提供消息内容"}), 400
    
    user_message = data['message']
    
    bot_response, detected_emotion, confidence = generate_response(user_message)
    
    return jsonify({
        "user_message": user_message,
        "bot_response": bot_response,
        "detected_emotion": detected_emotion,
        "confidence": confidence
    })

# ------------------------------
# 精美界面 - 匹配截图风格
# ------------------------------
@app.route('/')
def index():
    return render_template_string("""
    <!DOCTYPE html>
    <html lang="zh-CN">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>情感聊天机器人</title>
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
            
            .emoji-container {
                display: flex;
                justify-content: center;
                padding: 15px 0;
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
                font-weight: 600;
            }
            
            .welcome-card p {
                color: #666;
                font-size: 15px;
                line-height: 1.6;
                margin-bottom: 15px;
            }
            
            .emotion-tag {
                display: inline-block;
                background-color: #f0f3ff;
                color: #4a62e2;
                font-size: 14px;
                padding: 5px 12px;
                border-radius: 15px;
                margin: 0 3px;
                border: 1px solid #dfe4ff;
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
            }
        </style>
    </head>
    <body>
        <div class="chat-container">
            <div class="chat-header">
                <h1>情感聊天机器人</h1>
                <p>我能理解你的感受并做出有同理心的回应</p>
            </div>
            
            <div class="chat-box" id="chatBox">
                <div class="welcome-card">
                    <h3>👋 欢迎使用情感聊天机器人</h3>
                    <p>我是专注于情感理解的AI伙伴，你可以向我分享任何心情或想法。我会尽力理解并提供合适的回应。</p>
                    <div>
                        <span class="emotion-tag">高兴</span>
                        <span class="emotion-tag">伤心</span>
                        <span class="emotion-tag">生气</span>
                        <span class="emotion-tag">害怕</span>
                        <span class="emotion-tag">惊喜</span>
                    </div>
                </div>
                
                <div class="message">
                    <div class="bot-message">
                        <div class="message-content">你好！我是情感聊天机器人，可以随时和我分享你的心情～</div>
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
            // 辅助函数 - 获取当前时间
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
                    let emotionInfoHtml = '';
                    if (emotionInfo) {
                        emotionInfoHtml = `
                            <div class="emotion-info">
                                检测情感: ${emotionInfo.emotion} | 置信度: ${Math.round(emotionInfo.confidence * 100)}%
                            </div>
                        `;
                    }
                    
                    messageDiv.innerHTML = `
                        <div class="bot-message">
                            <div class="message-content">${content}</div>
                            <div class="timestamp">${timestamp}</div>
                            ${emotionInfoHtml}
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
                typingDiv.className = 'typing-indicator';
                typingDiv.id = 'typingIndicator';
                typingDiv.innerHTML = `
                    <div class="typing-dot"></div>
                    <div class="typing-dot"></div>
                    <div class="typing-dot"></div>
                `;
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
            
            // 处理发送消息
            async function sendMessage(content) {
                const sendBtn = document.getElementById('sendBtn');
                sendBtn.disabled = true;
                
                // 添加用户消息
                addMessage(content, true);
                document.getElementById('userInput').value = '';
                
                // 显示正在输入
                showTypingIndicator();
                
                try {
                    // 发送到API
                    const response = await fetch('/chat', {
                        method: 'POST',
                        headers: {
                            'Content-Type': 'application/json'
                        },
                        body: JSON.stringify({ message: content })
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
                    addMessage('暂时无法处理你的消息，请稍后再试', false);
                } finally {
                    sendBtn.disabled = false;
                    document.getElementById('userInput').focus();
                }
            }
            
            // 初始化事件
            document.addEventListener('DOMContentLoaded', function() {
                const sendBtn = document.getElementById('sendBtn');
                const userInput = document.getElementById('userInput');
                
                // 发送按钮事件
                sendBtn.addEventListener('click', function() {
                    const content = userInput.value.trim();
                    if (content) {
                        sendMessage(content);
                    }
                });
                
                // 输入框回车事件
                userInput.addEventListener('keypress', function(e) {
                    if (e.key === 'Enter') {
                        const content = userInput.value.trim();
                        if (content) {
                            sendMessage(content);
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
    print("情感聊天机器人服务启动...")
    print("访问 http://localhost:5000 开始聊天")
    app.run(host='0.0.0.0', port=5000, debug=False)