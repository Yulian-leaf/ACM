# GitHub 上传全流程（Windows + VS Code + SSH）

本文给出两种方式：
1) 手动命令（通用、最稳）
2) 一键脚本（本仓库已提供）

---

## 一、一次性准备（只需做一次）

### 1. 安装与身份信息
- 安装 Git for Windows
- 配置提交身份（建议全局一次设置）

```powershell
git config --global user.name "你的名字"
git config --global user.email "你的邮箱"
```

### 2. 配置 SSH（推荐）

1) 生成密钥（没有就生成）
```powershell
ssh-keygen -t ed25519 -C "你的邮箱"
```

2) 复制公钥并添加到 GitHub
```powershell
type $env:USERPROFILE\.ssh\id_ed25519.pub
```
GitHub → Settings → SSH and GPG keys → New SSH key

3) 测试 SSH
```powershell
ssh -T git@github.com
```
第一次会提示确认指纹，输入 `yes`。

---

## 二、每个新项目第一次上传（手动命令版）

在项目根目录执行：

```powershell
git init

# 重要：准备 .gitignore（避免把编译产物、缓存、大文件推上去）
# 如果没有就创建；有的话按需追加规则

git add -A
git commit -m "init"

git branch -M main

git remote add origin git@github.com:Yulian-leaf/ACM.git
git push -u origin main
```

---

## 三、后续更新（手动命令版）

每次改完代码：

```powershell
git status

git add -A
git commit -m "描述本次改动"

git push
```

---

## 四、一键脚本（推荐）

本仓库提供脚本：`scripts/git-init-push.ps1`

### 用法

在仓库根目录执行：

```powershell
powershell -ExecutionPolicy Bypass -File .\scripts\git-init-push.ps1 -RepoUrl "git@github.com:Yulian-leaf/ACM.git"
```

可选参数：
- `-Branch main`：分支名（默认 main）
- `-Message "init"`：提交信息
- `-Path "D:\\your\\project"`：指定要上传的目录（默认当前目录）
- `-NoCommit`：只 add，不 commit（适合你想手动写 commit message）
- `-DryRun`：仅打印将执行的 git 命令，不实际运行

---

## 五、常见问题

### 1) 推送提示大文件（>50MB）
- GitHub **推荐**单文件 <= 50MB；**硬限制** 100MB
- 解决：
  - 使用 Git LFS 管理大文件
  - 或把大文件加入 `.gitignore`，并从历史中移除后再推

### 2) SSH 权限失败
- 先跑：
```powershell
ssh -T git@github.com
```
- 再检查远程：
```powershell
git remote -v
```
应该看到 `git@github.com:...` 形式（SSH）。
