#include <algorithm>
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

  vector<Node> ns;       // 节点集合
  int last;              // 当前最后节点
  long long tot_sub;     // 不同子串总数
  long long tot_len;     // 所有子串出现次数×长度的总和
  long long max_product; // 存储最大乘积值
  SAM() {
    ns.push_back(Node());
    last = 0;
    tot_sub = 0;
    tot_len = 0;
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

    // 计算所有子串出现次数×长度的总和
    for (int i = 1; i < ns.size(); i++) {
      int minl = ns[ns[i].link].len + 1;
      int maxl = ns[i].len;
      int num = maxl - minl + 1;
      tot_len += ns[i].cnt * (long long)(minl + maxl) * num / 2;
    }
    // 计算所有子串出现次数×长度平方的总和
    int tot_sqsum{};
    for (int i = 1; i < ns.size(); i++) {
      int minl = ns[ns[i].link].len + 1;
      int maxl = ns[i].len;
      // 使用平方和公式：1²+2²+...+n² = n(n+1)(2n+1)/6
      long long sqsum_min = (minl - 1) * minl * (2 * minl - 1) / 6;
      long long sqsum_max = maxl * (maxl + 1) * (2 * maxl + 1) / 6;
      long long sqsum = sqsum_max - sqsum_min;

      tot_sqsum += ns[i].cnt * sqsum;
    }
    // 计算所有子串出现次数×长度的最大值
    for (int i = 0; i < ns.size(); i++) {
      long long product = ns[i].cnt * ns[i].len;
      if (product > max_product) {
        max_product = product;
      }
    }
  }

  // 返回不同子串总数
  long long sub_count() { return tot_sub; }

  // 返回所有子串出现次数×长度的总和
  long long len_sum() { return tot_len; }
};

int main() {
  int n;
  cin >> n;
  string s;
  cin >> s;

  SAM sam;
  sam.build(s);

  cout << sam.sub_count() << endl;
  // cout << sam.len_sum() << endl;

  return 0;
}