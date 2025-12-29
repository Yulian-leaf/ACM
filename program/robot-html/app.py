import torch
from transformers import pipeline, AutoTokenizer, AutoModelForSequenceClassification
from flask import Flask, request, jsonify, send_from_directory
import random
import time
import os
import re
import sys

# ============================= 修复部分 =============================
# 添加专门处理Windows控制台编码的设置
if sys.platform == "win32":
    # Windows控制台修复
    os.system("")  # 启用VT100转义序列支持
    # 确保标准输出正确编码
    if sys.stdout.encoding != 'utf-8':
        sys.stdout = open(sys.stdout.fileno(), 'w', encoding='utf-8', errors='ignore')
    if sys.stderr.encoding != 'utf-8':
        sys.stderr = open(sys.stderr.fileno(), 'w', encoding='utf-8', errors='ignore')

# 自定义安全打印函数
def safe_print(*args, **kwargs):
    """处理Windows平台的特殊打印问题"""
    try:
        message = " ".join(str(arg) for arg in args)
        # Windows安全处理
        if sys.platform == "win32":
            # 先尝试UTF-8编码
            try:
                print(message.encode('utf-8', 'ignore').decode('utf-8', 'ignore'), **kwargs)
            except:
                # 回退到控制台编码
                encoding = sys.stdout.encoding or 'utf-8'
                print(message.encode(encoding, 'ignore').decode(encoding, 'ignore'), **kwargs)
        else:
            # 其他平台正常打印
            print(message, **kwargs)
    except Exception as e:
        # 彻底失败时输出基本错误信息
        print(f"[PRINT ERROR] {e}", file=sys.stderr)

# ==================================================================

# 设置使用镜像源
os.environ['HF_ENDPOINT'] = 'https://hf-mirror.com'

app = Flask(__name__)

class EmotionalSupportBot:
    def __init__(self):
        safe_print("😊 初始化情感分析模型...")
        # 情感分析模型
        self.emotion_classifier = pipeline(
            "text-classification",
            model="bhadresh-savani/distilbert-base-uncased-emotion",
            return_all_scores=True
        )

        safe_print("💬 初始化响应生成模型...")
        # 情感响应模型
        self.response_generator = pipeline(
            "text2text-generation",
            model="google/flan-t5-base"
        )

        # 表情增强的共情回应库（英文）
        self.empathy_responses = {
            'sadness': [
                "😢 I hear that you're feeling down. I understand that feeling.",
                "🤗 Would you like to share more? I care about how you're feeling.",
                "💔 Feeling sad can be really tough, but remember these emotions are temporary.",
                "🤝 I know you're in pain right now, but please remember you're not alone.",
                "🌧️ Sometimes it's necessary to allow yourself to feel sad. I'm here with you."
            ],
            'joy': [
                "🎉 I'm so happy for you! These beautiful moments are worth cherishing.",
                "😄 That's wonderful! Could you tell me what made you so happy?",
                "🥰 Hearing this makes me happy too!",
                "🌈 This joyful feeling is so nice! Would you like to share more?",
                "☀️ It's heartwarming to see you happy."
            ],
            'anger': [
                "😠 I understand you must be feeling angry right now, and that's valid. This is a strong emotion, but what matters most is how we handle it.",
                "💢 Anger can be really troubling. Would you like to talk about what caused it?",
                "🧘 Take a deep breath and try to relax a little, okay?",
                "⚡ When we're angry, it's hard to think clearly. Can I help you sort through your thoughts?",
                "💥 Anger can be really troubling. Would you like to talk about what caused it?"
            ],
            'fear': [
                "😨 I sense you might be feeling uneasy. Fear is a natural human emotion.",
                "😰 When we're afraid, we often feel most alone, but remember you're not alone.",
                "👣 Sometimes the best way to face fear is to take small steps forward.",
                "🛡️ Fear is our brain's way of protecting us, though sometimes it overprotects.",
                "🤝 I'm here, and we can face what scares you together."
            ],
            'love': [
                "💖 It's beautiful to feel love, whether for others or for yourself.",
                "❤️ To love and be loved are among life's most precious experiences.",
                "💓 When we feel love, the whole world seems different.",
                "💕 Love truly gives life special meaning.",
                "💞 It's so heartwarming to hear you share about love in your life."
            ],
            'surprise': [
                "😲 How unexpected! Could you tell me what happened?",
                "🎊 Life is full of surprises. What surprised you this极简?",
                "🌀 Unexpected events can sometimes give us new perspectives.",
                "🎯 Sometimes surprises can become turning points. What do you think?",
                "✨ Wow! Could you tell me what surprised you so much?"
            ],
            'neutral': [
                "😌 I'm here to listen. Could you tell me more about how you're feeling?",
                "💬 What else would you like to share?",
                "🤔 That's interesting. Could you elaborate?",
                "🌱 Every experience helps us grow. Would you like to talk more about this?",
                "📝 I'm taking notes. Feel free to share anything on your mind."
            ]
        }

        # 表情与情感映射
        self.emoji_emotion_map = {
            "😠": "anger",
            "😡": "anger",
            "💢": "anger",
            "😤": "anger",
            "🤬": "anger",
            "😃": "joy",
            "😄": "joy",
            "😁": "joy",
            "🥳": "joy",
            "🤩": "joy",
            "😂": "joy",
            "😅": "joy",
            "😇": "joy",
            "🤣": "joy",
            "🙂": "joy",
            "😉": "joy",
            "😊": "joy",
            "🥰": "love",
            "😘": "love",
            "😍": "love",
            "❤️": "love",
            "💕": "love",
            "💘": "love",
            "💖": "love",
            "💗": "love",
            "💓": "love",
            "💞": "love",
            "🤗": "love",
            "😢": "sadness",
            "😭": "sadness",
            "😿": "sadness",
            "😓": "sadness",
            "😞": "sadness",
            "😔": "sadness",
            "🥺": "sadness",
            "😥": "sadness",
            "😰": "fear",
            "😨": "fear",
            "😧": "fear",
            "😬": "fear",
            "😱": "f极简r",
            "👻": "fear",
            "😲": "surprise",
            "😯": "surprise",
            "🤯": "surprise",
            "🤔": "neutral",
            "😐": "neutral",
            "😑": "neutral",
            "🙄": "neutral",
            "🧐": "neutral"
        }

        # 表情到描述词映射
        self.emoji_description = {
            "😠": "angry face",
            "😡": "pouting face",
            "😃": "smiling face",
            "😄": "smiling face with open mouth",
            "😁": "grinning face",
            "🥳": "partying face",
            "🤩": "star-struck face",
            "😂": "laughing with tears",
            "😅": "sweating smile",
            "😇": "smiling face with halo",
            "🤣": "rolling on the floor laughing",
            "🙂": "slight smile",
            "😉": "winking face",
            "😊": "smiling face with smiling eyes",
            "🥰": "smiling face with hearts",
            "😘": "face blowing kiss",
            "😍": "heart eyes",
            "❤️": "red heart",
            "💕": "two hearts",
            "💘": "heart with arrow",
            "💖": "sparkling heart",
            "💗": "growing heart",
            "💓": "beating heart",
            "💞": "revolving hearts",
            "🤗": "hugging face",
            "😢": "crying face",
            "😭": "loudly crying face",
            "😿": "crying cat",
            "😓": "downcast face with sweat",
            "😞": "disappointed face",
            "😔": "pensive face",
            "🥺": "pleading face",
            "😥": "sad but relieved face",
            "😰": "anxious face with sweat",
            "😨": "fearful face",
            "😧": "anguished face",
            "😬": "grimacing face",
            "😱": "face screaming in fear",
            "👻": "ghost",
            "😲": "astonished face",
            "😯": "hushed face",
            "🤯": "exploding head",
            "🤔": "thinking face",
            "😐": "neutral face",
            "😑": "expressionless face",
            "🙄": "face with rolling eyes",
            "🧐": "face with monocle"
        }

        safe_print("🤖 情感支持机器人初始化完成")

    def detect_emotion(self, user_input):
        if not user_input.strip():
            return None, ""

        # 检测表情符号及其描述
        emojis = [c for c in user_input if c in self.emoji_emotion_map]
        emoji_descriptions = [self.emoji_description.get(c, "emoji") for c in emojis]
        detected_emojis = ""

        # 分析情感逻辑
        try:
            emotions = self.emotion_classifier(user_input)[0]
            primary_emotion = max(emotions, key=lambda x: x['score'])
            base_emotion = primary_emotion['label']
            base_score = primary_emotion['score']

            # 合并表情情感分析
            if emojis:
                emoji_emotion = max(set(self.emoji_emotion_map[e] for e in emojis),
                                    key=[self.emoji_emotion_map[e] for e in emojis].count)
                emoji_confidence = len([e for e in emojis if self.emoji_emotion_map[e] == emoji_emotion]) / len(emojis)

                # 组合分析结果
                if emoji_confidence > 0.5 and base_score < 0.7:
                    final_emotion = emoji_emotion
                else:
                    final_emotion = base_emotion
            else:
                final_emotion = base_emotion

            detected_emojis = " ".join(emoji_descriptions) if emoji_descriptions else "None"
            safe_print(f"🎭 检测到的情感: {final_emotion} (文本: {base_emotion}, 表情: {detected_emojis})")
            return final_emotion, detected_emojis

        except Exception as e:
            safe_print(f"❗ 情感分析出错: {e}")
            detected_emojis = " ".join(emoji_descriptions) if emoji_descriptions else "None"
            return 'neutral', detected_emojis

    def generate_response(self, user_input, detected_emotion, detected_emojis):
        # 回应生成逻辑
        if detected_emotion in self.empathy_responses:
            response = random.choice(self.empathy_responses[detected_emotion])
            safe_print(f"💡 使用预设回应: {response}")
            return response

        # 构建包含表情描述的提示
        emoji_context = f"(noting that you used {detected_emojis})" if detected_emojis != "None" else ""
        prompt = f"Respond to this statement in a warm and friendly tone, showing care and understanding {emoji_context}. User says: {user_input}"
        safe_print(f"💭 生成回应提示: {prompt}")

        try:
            generated = self.response_generator(
                prompt,
                max_length=120,
                num_return_sequences=1,
                temperature=0.7
            )
            response = generated[0]['generated_text']
            safe_print(f"🤖 生成的回应: {response}")

            # 确保回应中有表情符号
            if not any(char in response for char in
                       "😀😁😂😃😄😅😆😉😊😋😎😍😘😗😙😚😇😐😑😶😏😣😥😮") and detected_emotion in self.empathy_responses:
                # 根据情感类型添加表情符号
                emotion_emojis = {
                    'anger': "😠",
                    'joy': "😄",
                    'sadness': "😢",
                    'fear': "😨",
                    'love': "❤️",
                    'surprise': "😲"
                }
                emoji = emotion_emojis.get(detected_emotion, "🤖")
                response = f"{emoji} {response}"

            return response
        except Exception as e:
            safe_print(f"❗ 生成回应出错: {e}")
            return "😕 I sense your emotions but I'm not sure how to respond. Could you tell me more?"

    def validate_response(self, response, user_input):
        # 验证逻辑
        if any(word in response.lower() for word in ["inappropriate", "negative", "harmful"]):
            return "🙏 I'm sorry, I'm not sure how to respond appropriately. Could we talk about something else?"

        if "don't understand" in response.lower() or "don't know" in response.lower():
            return f"📚 I'm still learning to better understand human emotions. You said '{user_input}', could you explain more?"

        return response


# 初始化机器人
safe_print("🤖 启动情感支持机器人...")
bot = EmotionalSupportBot()


@app.route('/chat', methods=['POST'])
def chat():
    safe_print("\n📩 收到聊天请求...")
    try:
        data = request.json
        user_input = data.get('message', '')
        safe_print(f"🗣️ 用户输入: {user_input}")

        if not user_input:
            return jsonify({
                'response': "😶 I didn't quite catch that. Could you repeat?",
                'emotion': 'neutral',
                'emojis': '',
                'end_conversation': False
            })

        if user_input.lower() in ['exit', 'quit', 'bye']:
            safe_print("👋 结束对话请求")
            return jsonify({
                'response': "💖 Thank you for sharing! Remember, you're not alone. I'm here whenever you need me.",
                'end_conversation': True
            })

        emotion, detected_emojis = bot.detect_emotion(user_input)
        response = bot.generate_response(user_input, emotion, detected_emojis)
        final_response = bot.validate_response(response, user_input)

        # 添加人性化延迟 (1-3秒)
        delay = 1 + random.random() * 2
        safe_print(f"⏳ 模拟思考延迟: {delay:.2f}秒")
        time.sleep(delay)

        safe_print(f"💬 发送回应: {final_response}")
        return jsonify({
            'response': final_response,
            'emotion': emotion,
            'emojis': detected_emojis,
            'end_conversation': False
        })

    except Exception as e:
        safe_print(f"❗ 聊天请求处理错误: {e}")
        return jsonify({
            'response': "😓 I'm having some trouble processing your request. Could you try again?",
            'emotion': 'neutral',
            'emojis': '',
            'end_conversation': False
        })


@app.route('/')
def index():
    """主页面服务路由 - 使用静态文件"""
    try:
        return send_from_directory('static', 'index.html')
    except Exception as e:
        safe_print(f"❗ 首页加载错误: {e}")
        return f'''
        <html><body>
            <h1>Emotional Support Bot</h1>
            <p>The bot is running properly but experienced a display issue.</p>
            <p>Debug information: {str(e)}</p>
        </body></html>
        ''', 200


@app.route('/ping')
def ping():
    return jsonify({
        'status': 'alive',
        'message': 'Enhanced Emotional Support Bot is running',
        'version': '2.0',
        'features': ['emoji_detection', 'anger_support']
    })


if __name__ == '__main__':
    # 启动部分
    safe_print("🚀 启动Flask应用...")
    port = 5000
    started = False
    max_attempts = 5

    for attempt in range(max_attempts):
        try:
            safe_print(f"🔌 尝试在端口 {port} 启动服务...")
            app.run(debug=False, host='0.0.0.0', port=port, use_reloader=False)
            started = True
            break
        except OSError as e:
            safe_print(f"❌ 端口 {port} 启动失败: {str(e)}")
            if "Address already in use" in str(e):
                safe_print(f"🔄 端口 {port} 已被占用，尝试新端口")
                port += 1
            else:
                safe_print(f"⚠️ 启动错误: {str(e)}")
                break

    if not started:
        safe_print(f"\n⛔ 无法启动服务，所有尝试端口 ({port - max_attempts} 到 {port}) 均不可用")
        safe_print("🛠️ 请关闭其他程序或指定端口: python app.py --port=YOUR_PORT_NUMBER")  