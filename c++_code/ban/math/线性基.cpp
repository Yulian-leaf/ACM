#include <bits/stdc++.h>
using namespace std;
#define Endl "\n"
#define INF 0x3f3f3f3f
#define PI 3.14159265358979323846 // 20f
const int MOD = 998244353;
// const int MOD = 1e9 + 7;
typedef long long ll;
typedef unsigned long long ull;
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
#define int ll

#include <algorithm>
#include <map>
#include <vector>
using namespace std;

class LinearBasis {
private:
  static const int MAX_BIT = 63;   // 最大位数（处理64位整数）
  vector<long long> base;          // 基向量
  vector<long long> rebuiltBase;   // 重构后的基（用于查询第K小）
  vector<int> timeStamp;           // 每个基向量的时间戳（最后更新时间）
  map<long long, int> elementTime; // 元素及其插入时间
  int currentTime;                 // 当前时间戳
  bool zeroFlag;                   // 是否能表示0（存在线性相关）
  bool needRebuild;                // 是否需要重构标志

public:
  LinearBasis() {
    base.resize(MAX_BIT + 1, 0);
    timeStamp.resize(MAX_BIT + 1, -1); // -1表示该位置未被使用
    currentTime = 0;
    zeroFlag = false;
    needRebuild = false;
  }

  /**
   * 插入一个数字
   * 时间复杂度: O(log(max_val))
   * @param x 要插入的数字
   */
  void insert(long long x) {
    currentTime++;
    elementTime[x] = currentTime; // 记录元素的插入时间

    int lastChanged = -1;
    for (int i = MAX_BIT; i >= 0; i--) {
      if (!(x >> i))
        continue; // 跳过高位0

      if (!base[i]) {
        base[i] = x;
        timeStamp[i] = currentTime;
        needRebuild = true;
        return;
      }

      // 如果当前基的时间戳更早，则交换
      if (timeStamp[i] < currentTime) {
        swap(base[i], x);
        swap(timeStamp[i], currentTime);
      }

      x ^= base[i];
    }

    // 如果执行到这里说明x被消为0
    zeroFlag = true;
    needRebuild = true;
  }

  /**
   * 删除一个数字
   * 时间复杂度: O(n * log(max_val))，其中n是插入的元素数量
   * @param x 要删除的数字
   */
  void erase(long long x) {
    auto it = elementTime.find(x);
    if (it == elementTime.end())
      return; // 元素不存在

    int t = it->second;
    elementTime.erase(it);

    // 找到所有时间戳大于等于t的基向量
    for (int i = 0; i <= MAX_BIT; i++) {
      if (timeStamp[i] >= t) {
        base[i] = 0;
        timeStamp[i] = -1;
      }
    }

    // 重新插入所有时间戳大于t的元素
    vector<long long> toReinsert;
    for (auto &p : elementTime) {
      if (p.second > t) {
        toReinsert.push_back(p.first);
      }
    }

    // 清空当前基
    fill(base.begin(), base.end(), 0);
    fill(timeStamp.begin(), timeStamp.end(), -1);
    zeroFlag = false;
    currentTime = 0;

    // 重新插入所有元素
    for (auto elem : toReinsert) {
      insert(elem);
    }
  }

  /**
   * 查询最大异或和
   * 时间复杂度: O(log(max_val))
   * @return 最大异或和
   */
  long long queryMax() {
    long long res = 0;
    for (int i = MAX_BIT; i >= 0; i--) {
      if (base[i] && (res ^ base[i]) > res) {
        res ^= base[i];
      }
    }
    return res;
  }

  /**
   * 查询最小异或和
   * 时间复杂度: O(log(max_val))
   * @return 最小异或和
   */
  long long queryMin() {
    if (zeroFlag)
      return 0; // 0是最小值
    for (int i = 0; i <= MAX_BIT; i++) {
      if (base[i])
        return base[i];
    }
    return 0; // 所有基为0
  }

  /**
   * 判断数字x是否能被表示
   * 时间复杂度: O(log(max_val))
   * @param x 要检查的数字
   * @return 是否可表示
   */
  bool check(long long x) {
    for (int i = MAX_BIT; i >= 0; i--) {
      if (x >> i)
        x ^= base[i];
    }
    return x == 0;
  }

private:
  /**
   * 重构线性基（用于查询第K小）
   * 时间复杂度: O((log(max_val))^2)
   */
  void rebuild() {
    rebuiltBase.clear();
    // 复制当前基
    vector<long long> temp = base;

    // 高斯消元：从低位到高位消元
    for (int i = 0; i <= MAX_BIT; i++) {
      if (!temp[i])
        continue;
      // 用低位基消去高位基的对应位
      for (int j = 0; j < i; j++) {
        if (temp[i] >> j & 1) {
          temp[i] ^= temp[j];
        }
      }
      if (temp[i]) {
        rebuiltBase.push_back(temp[i]);
      }
    }
    needRebuild = false;
  }

public:
  /**
   * 查询第K小异或和（K从1开始）
   * 时间复杂度: O((log(max_val))^2)（如果需要重构）
   *             或 O(log(max_val))（如果不需要重构）
   * @param k 第K小
   * @return 第K小的异或和，如果不存在返回-1
   */
  long long queryKth(long long k) {
    // 处理特殊情况：0的存在
    if (zeroFlag) {
      if (k == 1)
        return 0;
      k--; // 跳过0
    } else if (k == 1) {
      return 0; // 即使没有线性相关，0也是第一小（空集）
    }

    // 检查是否需要重构
    if (needRebuild)
      rebuild();

    int m = rebuiltBase.size();
    // 如果k超过最大表示数量
    if (k > (1LL << m))
      return -1;

    // 用k的二进制位组合基向量
    long long res = 0;
    k--; // 因为0已处理，现在k从1开始对应第一个非0组合
    for (int i = 0; i < m; i++) {
      if (k >> i & 1) {
        res ^= rebuiltBase[i];
      }
    }
    return res;
  }

  /**
   * 获取当前基向量数量
   * 时间复杂度: O(log(max_val))
   * @return 基向量数量
   */
  int size() {
    int cnt = 0;
    for (int i = 0; i <= MAX_BIT; i++) {
      if (base[i])
        cnt++;
    }
    return cnt;
  }
};

int main() {
  LinearBasis lb;

  // 插入元素
  lb.insert(5);
  lb.insert(12);
  lb.insert(3);

  // 查询最大异或和
  cout << "Max XOR: " << lb.queryMax() << endl; // O(log(max_val))

  // 查询最小异或和
  cout << "Min XOR: " << lb.queryMin() << endl; // O(log(max_val))

  // 检查数字是否可表示
  cout << "Check 6: " << lb.check(6) << endl; // O(log(max_val))

  // 查询第K小异或和
  cout << "Kth(1): " << lb.queryKth(1) << endl; // O((log(max_val))^2)
  cout << "Kth(2): " << lb.queryKth(2) << endl;

  // 删除元素
  lb.erase(3); // O(n * log(max_val))
  cout << "After deleting 3, Max XOR: " << lb.queryMax() << endl;

  return 0;
}