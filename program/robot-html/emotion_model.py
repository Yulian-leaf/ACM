import os
import torch
from flask import Flask, request, jsonify, render_template_string
from transformers import BertTokenizer, BertForSequenceClassification
import numpy as np
from scipy.special import softmax
import time
import re
import random

# 初始化Flask应用
app = Flask(__name__)

# ------------------------------
# 情感分析模型 - 本地化加载解决方案
# ------------------------------

# 模型文件目录
MODEL_DIR = "./saved_model"
MODEL_PATH = os.path.join(MODEL_DIR, "pytorch_model.bin")
CONFIG_PATH = os.path.join(MODEL_DIR, "config.json")
VOCAB_PATH = os.path.join(MODEL_DIR, "vocab.txt")

# 确保目录存在
os.makedirs(MODEL_DIR, exist_ok=True)

def download_model_files():
    """下载模型所需文件到本地"""
    print("正在下载模型文件...")
    try:
        # 下载模型、配置和词汇表
        tokenizer = BertTokenizer.from_pretrained("bert-base-chinese")
        model = BertForSequenceClassification.from_pretrained("bert-base-chinese", num_labels=6)
        
        # 保存文件到本地
        tokenizer.save_pretrained(MODEL_DIR)
        model.save_pretrained(MODEL_DIR)
        
        print("模型文件下载并保存完成")
        return True
    except Exception as e:
        print(f"下载模型文件失败: {str(e)}")
        return False

def load_model():
    """从本地文件加载模型，如果没有则下载"""
    # 检查文件是否存在
    if not os.path.exists(MODEL_PATH) or not os.path.exists(VOCAB_PATH):
        print("未找到本地模型文件")
        if not download_model_files():
            print("无法下载模型文件，将使用简化模型")
            return None, None
    
    print("正在从本地加载模型...")
    try:
        # 加载tokenizer
        tokenizer = BertTokenizer.from_pretrained(MODEL_DIR)
        
        # 加载模型配置和权重
        model = BertForSequenceClassification.from_pretrained(MODEL_DIR, num_labels=6)
        
        print("模型加载成功")
        return model, tokenizer
    except Exception as e:
        print(f"从本地加载模型失败: {str(e)}")
        return None, None

# 加载模型
model, tokenizer = load_model()

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

def analyze_sentiment_with_model(text):
    """使用BERT模型进行情感分析"""
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
    probabilities = softmax(logits, axis=1)[0]
    
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

def fallback_sentiment_analysis(text):
    """当BERT模型不可用时的后备情感分析方法"""
    # 简化的基于规则的情感分析
    positive_words = ['开心', '高兴', '快乐', '喜欢', '爱', '笑', '幸福', '满意']
    negative_words = ['生气', '愤怒', '伤心', '难过', '哭', '痛苦', '失望', '恨']
    
    # 检查情绪词
    for word in positive_words:
        if word in text:
            return 'joy', 0.75
    for word in negative_words:
        if word in text:
            return 'sadness', 0.75
    
    # 默认情绪
    return 'neutral', 0.6

def analyze_sentiment(text):
    """统一的情感分析接口"""
    # 如果模型可用，使用模型
    if model and tokenizer:
        return analyze_sentiment_with_model(text)
    else:
        print("使用后备情感分析方法")
        return fallback_sentiment_analysis(text)

# ------------------------------
# 响应生成系统
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
    """根据情感和置信度生成响应"""
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
# 完整的界面实现（与之前相同）
# ------------------------------

# 这里是之前完整的HTML界面代码，为了简洁已省略
# 实际使用时需要包含前面提供的完整HTML界面代码

if __name__ == '__main__':
    print("情感聊天机器人服务启动...")
    if model and tokenizer:
        print("情感分析模型: BERT-base-chinese")
    else:
        print("情感分析模型: 简化版规则系统")
    print("访问 http://localhost:5000 开始使用")
    app.run(host='0.0.0.0', port=5000, debug=True)