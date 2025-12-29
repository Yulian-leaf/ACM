#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

struct SAM {
  struct Node {
    int len;       // 最长子串长度
    int link;      // 后缀链接
    long long cnt; // 出现次数
    int pos;       // 第一次出现位置
    int nxt[26];   // 转移边

    Node() : len(0), link(-1), cnt(0), pos(-1) { memset(nxt, -1, sizeof(nxt)); }
  };

  vector<Node> ns;   // 节点集合
  int last;          // 当前最后节点
  long long tot_sub; // 不同子串总数

  SAM() {
    ns.push_back(Node());
    last = 0;
    tot_sub = 0;
  }

  void add(char c) {
    int cur = ns.size();
    ns.push_back(Node());
    ns[cur].len = ns[last].len + 1;
    ns[cur].pos = ns[cur].len - 1;
    ns[cur].cnt = 1;

    int p = last;
    while (p != -1 && ns[p].nxt[c - 'a'] == -1) {
      ns[p].nxt[c - 'a'] = cur;
      p = ns[p].link;
    }

    if (p == -1) {
      ns[cur].link = 0;
    } else {
      int q = ns[p].nxt[c - 'a'];
      if (ns[p].len + 1 == ns[q].len) {
        ns[cur].link = q;
      } else {
        int nq = ns.size();
        ns.push_back(ns[q]);
        ns[nq].len = ns[p].len + 1;
        ns[nq].cnt = 0;

        ns[q].link = nq;
        ns[cur].link = nq;

        while (p != -1 && ns[p].nxt[c - 'a'] == q) {
          ns[p].nxt[c - 'a'] = nq;
          p = ns[p].link;
        }
      }
    }

    // 更新不同子串总数
    tot_sub += ns[cur].len - ns[ns[cur].link].len;

    last = cur;
  }

  void build(const string &s) {
    for (char c : s)
      add(c);

    // 拓扑排序
    vector<int> ord(ns.size());
    for (int i = 0; i < ns.size(); i++)
      ord[i] = i;
    sort(ord.begin(), ord.end(),
         [&](int i, int j) { return ns[i].len > ns[j].len; });

    // 传递出现次数
    for (int i : ord) {
      if (ns[i].link != -1) {
        ns[ns[i].link].cnt += ns[i].cnt;
      }
    }
  }

  // 计算第k大重要子串（重要性 = 出现次数 × 长度²）
  long long kth_important_substring(long long k) {
    // 计算总子串数（每个状态包含的子串个数之和）
    long long total_substrings = 0;
    for (int i = 1; i < ns.size(); i++) {
      int minl = ns[ns[i].link].len + 1;
      int maxl = ns[i].len;
      total_substrings += (maxl - minl + 1);
    }

    // 如果k大于总子串数，返回0
    if (k > total_substrings) {
      return 0;
    }

    // 二分答案
    long long low = 0;
    long long high = 0;
    for (int i = 1; i < ns.size(); i++) {
      long long max_val = ns[i].cnt * (long long)ns[i].len * ns[i].len;
      if (max_val > high)
        high = max_val;
    }

    long long ans = 0;
    while (low <= high) {
      long long mid = (low + high) / 2;
      long long count = 0; // 统计重要性≥mid的子串数量

      for (int i = 1; i < ns.size(); i++) {
        auto &node = ns[i];
        if (node.cnt == 0)
          continue;

        if (mid == 0) {
          // 所有子串都满足条件
          int minl = ns[node.link].len + 1;
          count += (node.len - minl + 1);
        } else {
          // 计算最小满足条件的长度
          double tmp = (double)mid / node.cnt;
          long long l0 = ceil(sqrt(tmp));
          int minl = ns[node.link].len + 1;
          long long L = max(l0, (long long)minl);

          if (L <= node.len) {
            count += (node.len - L + 1);
          }
        }
      }

      if (count >= k) {
        ans = mid;
        low = mid + 1;
      } else {
        high = mid - 1;
      }
    }

    return ans;
  }
};

int main() {
  int n;
  long long k;
  cin >> n >> k;
  string s;
  cin >> s;

  SAM sam;
  sam.build(s);

  cout << sam.kth_important_substring(k) << endl;

  return 0;
}