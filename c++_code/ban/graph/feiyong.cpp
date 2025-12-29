#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;
typedef long long ll;
#define int ll
typedef unsigned long long ull;
const int INF = 2e18;

// 时间复杂度O(m*n*f)
// m是边数, n是点数, f是最大流

struct MinCostMaxFlow {
  struct Edge {
    int v;   // 目标顶点
    ll cap;  // 容量
    ll cost; // 单位流量费用
    ll flow; // 当前流量
    int rev; // 反向边在邻接表中的索引
  };

  int n;                      // 顶点总数
  int S, T;                   // 源点和汇点
  ll maxflow;                 // 最大流
  ll mincost;                 // 最小费用
  vector<vector<Edge>> graph; // 图的邻接表
  vector<ll> dist;            // 最短路径距离
  vector<int> pre;            // 前驱节点
  vector<int> pre_edge;       // 前驱边索引
  vector<bool> inq;           // SPFA队列标记

  // 构造函数：初始化最小费用最大流算法
  MinCostMaxFlow(int num_nodes, int source, int sink)
      : n(num_nodes), S(source), T(sink), maxflow(0), mincost(0) {
    graph.resize(n + 1);
    dist.resize(n + 1);
    pre.resize(n + 1);
    pre_edge.resize(n + 1);
    inq.resize(n + 1);
  }

  // 添加边：u->v，容量cap，单位费用cost
  void addedge(int u, int v, ll cap, ll cost) {
    // 添加正向边
    graph[u].push_back({v, cap, cost, 0, (int)graph[v].size()});
    // 添加反向边（容量0，费用-cost）
    graph[v].push_back({u, 0, -cost, 0, (int)graph[u].size() - 1});
  }

  // SPFA算法寻找费用最小的增广路
  bool spfa() {
    fill(dist.begin(), dist.end(), INF);
    fill(inq.begin(), inq.end(), false);

    queue<int> q;
    dist[S] = 0;
    inq[S] = true;
    q.push(S);

    while (!q.empty()) {
      int u = q.front();
      q.pop();
      inq[u] = false;

      for (int i = 0; i < graph[u].size(); i++) {
        Edge &e = graph[u][i];
        int v = e.v;
        // 检查是否有剩余容量且可以松弛
        if (e.cap > e.flow && dist[v] > dist[u] + e.cost) {
          dist[v] = dist[u] + e.cost;
          pre[v] = u;
          pre_edge[v] = i;

          if (!inq[v]) {
            inq[v] = true;
            q.push(v);
          }
        }
      }
    }
    return dist[T] != INF; // 返回汇点是否可达
  }

  // 执行最小费用最大流算法
  void dinic() {
    maxflow = 0;
    mincost = 0;

    while (spfa()) {
      ll min_cap = INF; // 本次增广的最大流量

      // 回溯路径，计算最小剩余容量
      for (int v = T; v != S; v = pre[v]) {
        int u = pre[v];
        int i = pre_edge[v];
        min_cap = min(min_cap, graph[u][i].cap - graph[u][i].flow);
      }

      // 更新路径上的流量
      for (int v = T; v != S; v = pre[v]) {
        int u = pre[v];
        int i = pre_edge[v];
        Edge &e = graph[u][i];
        e.flow += min_cap;
        graph[v][e.rev].flow -= min_cap;
      }

      maxflow += min_cap;
      mincost += min_cap * dist[T];
    }
  }
};
void work() {
  int n, m, s, t;
  cin >> n >> m >> s >> t;
  MinCostMaxFlow mf(n, s, t);
  for (int i = 1; i <= m; i++) {
    int u, v, w, c;
    cin >> u >> v >> w >> c;
    mf.addedge(u, v, w, c);
  }
  mf.dinic();
  cout << mf.maxflow << ' ' << mf.mincost << '\n';
}

#undef int
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  // cout << fixed << setprecision(2);
  int T = 1;
  // cin >> T;
  while (T--) {
    work();
  }
}