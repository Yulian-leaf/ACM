import cv2
import numpy as np
import librosa
import torch
import torch.nn as nn
from transformers import pipeline, AutoModel, AutoTokenizer
from facenet_pytorch import MTCNN, InceptionResnetV1
import speech_recognition as sr
from collections import Counter
import warnings
warnings.filterwarnings('ignore')

class MultimodalEmotionRecognizer:
    def __init__(self):
        # 初始化各模态处理器
        self.visual_processor = VisualEmotionProcessor()
        self.audio_processor = AudioEmotionProcessor()
        self.text_processor = TextEmotionProcessor()
        self.fusion_model = MultimodalFusion()
        
    def analyze_video(self, video_path):
        """主分析方法：处理视频文件"""
        # 1. 提取视觉特征（人脸表情）
        visual_results = self.visual_processor.process_video(video_path)
        
        # 2. 提取音频特征（语音语调）
        audio_results = self.audio_processor.process_audio(video_path)
        
        # 3. 语音识别并提取文本情感
        text_results = self.text_processor.process_video_text(video_path)
        
        # 4. 多模态融合
        final_emotion = self.fusion_model.fuse_modalities(
            visual_results, audio_results, text_results
        )
        
        return {
            'final_emotion': final_emotion,
            'visual_emotion': visual_results,
            'audio_emotion': audio_results,
            'text_emotion': text_results
        }

class VisualEmotionProcessor:
    """计算机视觉模块：处理人脸表情识别"""
    
    def __init__(self):
        # 使用预训练的人脸检测和表情识别模型
        self.face_detector = MTCNN(keep_all=True)
        self.emotion_model = self._load_emotion_model()
        
    def _load_emotion_model(self):
        """加载表情识别模型"""
        # 使用FER2013预训练模型
        try:
            # 尝试加载预训练的表情识别模型
            model = torch.hub.load('pytorch/vision:v0.10.0', 'resnet18', pretrained=True)
            # 修改最后一层用于7类情绪分类
            model.fc = nn.Linear(model.fc.in_features, 7)  # 7种基本情绪
            
            # 注意：这里需要加载预训练权重，但为了简化我们先使用随机初始化
            # 实际应用中应该加载在FER2013等数据集上预训练的权重
            return model
        except:
            # 如果下载失败，创建一个简单的CNN模型
            print("下载预训练模型失败，使用简化模型")
            return self._create_simple_model()
    
    def _create_simple_model(self):
        """创建简化的CNN模型"""
        class SimpleCNN(nn.Module):
            def __init__(self, num_classes=7):
                super(SimpleCNN, self).__init__()
                self.conv1 = nn.Conv2d(3, 32, 3, padding=1)
                self.conv2 = nn.Conv2d(32, 64, 3, padding=1)
                self.pool = nn.MaxPool2d(2, 2)
                self.fc1 = nn.Linear(64 * 56 * 56, 128)
                self.fc2 = nn.Linear(128, num_classes)
                self.dropout = nn.Dropout(0.5)
                self.relu = nn.ReLU()
                
            def forward(self, x):
                x = self.pool(self.relu(self.conv1(x)))
                x = self.pool(self.relu(self.conv2(x)))
                x = x.view(x.size(0), -1)
                x = self.relu(self.fc1(x))
                x = self.dropout(x)
                x = self.fc2(x)
                return x
                
        return SimpleCNN()
    
    def _aggregate_emotions(self, emotions):
        """聚合多帧的情绪结果（添加缺失的方法）"""
        if not emotions:
            return 'neutral'
        
        # 过滤掉None值
        valid_emotions = [e for e in emotions if e is not None]
        
        if not valid_emotions:
            return 'neutral'
        
        # 使用多数投票决定最终情绪
        emotion_counter = Counter(valid_emotions)
        most_common_emotion = emotion_counter.most_common(1)[0][0]
        
        return most_common_emotion
    
    def process_video(self, video_path):
        """处理视频帧序列"""
        cap = cv2.VideoCapture(video_path)
        emotions = []
        frame_count = 0
        max_frames = 100  # 限制处理的帧数，避免处理时间过长
        
        while cap.isOpened() and frame_count < max_frames:
            ret, frame = cap.read()
            if not ret:
                break
                
            # 每5帧处理一次，提高效率
            if frame_count % 5 == 0:
                # 检测人脸并识别表情
                emotion = self._analyze_frame(frame)
                emotions.append(emotion)
            
            frame_count += 1
        
        cap.release()
        return self._aggregate_emotions(emotions)
    
    def _analyze_frame(self, frame):
        """分析单帧图像的表情"""
        try:
            # 转换BGR到RGB
            frame_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
            
            # 人脸检测
            boxes, probs = self.face_detector.detect(frame_rgb)
            
            if boxes is not None:
                # 提取人脸区域并进行表情分类
                for i, (box, prob) in enumerate(zip(boxes, probs)):
                    if prob > 0.9:  # 置信度阈值
                        x1, y1, x2, y2 = [int(coord) for coord in box]
                        # 确保坐标在图像范围内
                        x1, y1 = max(0, x1), max(0, y1)
                        x2, y2 = min(frame.shape[1], x2), min(frame.shape[0], y2)
                        
                        face_roi = frame[y1:y2, x1:x2]
                        
                        if face_roi.size > 0:
                            # 预处理并预测表情
                            emotion = self._predict_emotion(face_roi)
                            return emotion
            return None
        except Exception as e:
            print(f"视觉处理错误: {e}")
            return None
    
    def _predict_emotion(self, face_image):
        """预测单张人脸图像的情绪"""
        try:
            # 图像预处理
            face_image = cv2.resize(face_image, (224, 224))
            face_tensor = torch.tensor(face_image).permute(2, 0, 1).float().unsqueeze(0) / 255.0
            
            # 预测
            with torch.no_grad():
                outputs = self.emotion_model(face_tensor)
                _, predicted = torch.max(outputs, 1)
            
            emotion_labels = ['angry', 'disgust', 'fear', 'happy', 'sad', 'surprise', 'neutral']
            return emotion_labels[predicted.item()]
        except:
            # 如果模型预测失败，返回中性情绪
            return 'neutral'

class AudioEmotionProcessor:
    """音频处理模块：分析语音语调情绪"""
    
    def __init__(self):
        self.emotion_labels = ['neutral', 'calm', 'happy', 'sad', 'angry', 'fearful', 'disgust', 'surprised']
    
    def process_audio(self, video_path):
        """从视频中提取音频并分析情绪"""
        try:
            # 提取音频
            audio, sr = librosa.load(video_path, sr=22050)
            
            # 提取音频特征
            features = self._extract_audio_features(audio, sr)
            
            # 情绪分类
            emotion = self._classify_emotion(features)
            
            return emotion
        except Exception as e:
            print(f"音频处理错误: {e}")
            return 'neutral'
    
    def _extract_audio_features(self, audio, sr):
        """提取音频特征"""
        features = {}
        
        try:
            # MFCC特征
            mfccs = librosa.feature.mfcc(y=audio, sr=sr, n_mfcc=13)
            features['mfcc_mean'] = np.mean(mfccs, axis=1)
            features['mfcc_std'] = np.std(mfccs, axis=1)
            
            # 音调特征
            pitches, magnitudes = librosa.piptrack(y=audio, sr=sr)
            valid_pitches = pitches[pitches > 0]
            features['pitch_mean'] = np.mean(valid_pitches) if len(valid_pitches) > 0 else 100
            
            # 能量特征
            features['energy'] = np.mean(audio**2)
            
            # 频谱质心
            features['spectral_centroid'] = np.mean(librosa.feature.spectral_centroid(y=audio, sr=sr))
            
        except Exception as e:
            print(f"音频特征提取错误: {e}")
            # 设置默认值
            features['pitch_mean'] = 100
            features['energy'] = 0.05
        
        return features
    
    def _classify_emotion(self, features):
        """基于音频特征进行情绪分类"""
        try:
            energy = features['energy']
            pitch = features['pitch_mean']
            
            if energy > 0.1 and pitch > 200:
                return 'happy'
            elif energy < 0.05 and pitch < 100:
                return 'sad'
            elif energy > 0.15:
                return 'angry'
            elif pitch > 180:
                return 'surprised'
            else:
                return 'neutral'
        except:
            return 'neutral'

class TextEmotionProcessor:
    """自然语言处理模块：分析文本情绪"""
    
    def __init__(self):
        try:
            # 使用轻量级的情感分析模型，避免下载大模型
            self.sentiment_analyzer = pipeline(
                "text-classification",
                model="distilbert-base-uncased-finetuned-sst-2-english",
                top_k=1
            )
        except:
            # 如果模型加载失败，使用简单规则
            self.sentiment_analyzer = None
    
    def process_video_text(self, video_path):
        """从视频中提取文本并分析情绪"""
        try:
            # 语音识别
            text = self._speech_to_text(video_path)
            
            if text and len(text.strip()) > 5:  # 确保有足够的文本内容
                emotion = self._analyze_text_emotion(text)
                return emotion
            else:
                return 'neutral'
        except Exception as e:
            print(f"文本处理错误: {e}")
            return 'neutral'
    
    def _speech_to_text(self, video_path):
        """语音识别"""
        try:
            # 简化版：直接返回示例文本
            # 实际应用中应该实现完整的语音识别
            return "This is a sample text for emotion analysis. I am feeling happy today."
        except:
            return ""
    
    def _analyze_text_emotion(self, text):
        """分析文本情绪"""
        if self.sentiment_analyzer is None:
            # 简单规则作为备选
            positive_words = ['happy', 'good', 'great', 'excellent', 'wonderful', 'amazing']
            negative_words = ['sad', 'bad', 'terrible', 'awful', 'horrible', 'angry']
            
            text_lower = text.lower()
            positive_count = sum(1 for word in positive_words if word in text_lower)
            negative_count = sum(1 for word in negative_words if word in text_lower)
            
            if positive_count > negative_count:
                return 'happy'
            elif negative_count > positive_count:
                return 'sad'
            else:
                return 'neutral'
        else:
            try:
                result = self.sentiment_analyzer(text[:512])  # 限制文本长度
                sentiment = result[0][0]['label']
                if sentiment == 'POSITIVE':
                    return 'happy'
                else:
                    return 'sad'
            except:
                return 'neutral'

class MultimodalFusion:
    """多模态融合模块"""
    
    def __init__(self):
        # 定义各模态的权重
        self.weights = {
            'visual': 0.4,
            'audio': 0.35,
            'text': 0.25
        }
    
    def fuse_modalities(self, visual_emotion, audio_emotion, text_emotion):
        """融合三种模态的情绪结果"""
        # 情绪映射到统一的空间
        emotion_scores = {
            'happy': 0, 'sad': 0, 'angry': 0, 
            'fear': 0, 'surprise': 0, 'disgust': 0, 'neutral': 0
        }
        
        # 累加各模态的情绪得分
        self._add_emotion_score(emotion_scores, visual_emotion, self.weights['visual'])
        self._add_emotion_score(emotion_scores, audio_emotion, self.weights['audio'])
        self._add_emotion_score(emotion_scores, text_emotion, self.weights['text'])
        
        # 选择得分最高的情绪作为最终结果
        final_emotion = max(emotion_scores.items(), key=lambda x: x[1])
        return final_emotion[0]
    
    def _add_emotion_score(self, emotion_scores, emotion, weight):
        """为特定情绪添加得分"""
        # 处理情绪标签的映射
        emotion_mapping = {
            'calm': 'neutral',
            'fearful': 'fear',
            'surprised': 'surprise',
            'disgusted': 'disgust',
            'POSITIVE': 'happy',
            'NEGATIVE': 'sad'
        }
        
        actual_emotion = emotion_mapping.get(emotion, emotion)
        
        if actual_emotion in emotion_scores:
            emotion_scores[actual_emotion] += weight

# 使用示例
if __name__ == "__main__":
    # 初始化系统
    recognizer = MultimodalEmotionRecognizer()
    
    # 由于可能没有视频文件，我们创建一个模拟测试
    print("正在初始化多模态情绪识别系统...")
    
    # 模拟测试 - 实际使用时请替换为真实视频路径
    try:
        # 尝试使用OpenCV创建一个简单的测试视频
        test_video_path = r"D:\vs study\python_code\a.mp4"
        
        # 创建一个简单的测试视频（如果不存在）
        import os
        if not os.path.exists(test_video_path):
            print("未找到测试视频，将使用模拟数据进行演示...")
            # 模拟结果
            result = {
                'final_emotion': 'happy',
                'visual_emotion': 'happy',
                'audio_emotion': 'neutral', 
                'text_emotion': 'happy'
            }
        else:
            # 分析真实视频
            result = recognizer.analyze_video(test_video_path)
        
        print("多模态情绪分析结果:")
        print(f"最终情绪: {result['final_emotion']}")
        print(f"视觉情绪: {result['visual_emotion']}")
        print(f"音频情绪: {result['audio_emotion']}")
        print(f"文本情绪: {result['text_emotion']}")
        
    except Exception as e:
        print(f"测试过程中出现错误: {e}")
        print("这可能是因为缺少测试视频文件或依赖库问题")