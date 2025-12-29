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
struct MaxFlow {
  struct Edge {
    int v;    // 目标顶点
    int cap;  // 容量
    int flow; // 当前流量 ----> 可以知道每条边流经的流量
    int rev;  // 反向边在邻接表中的索引
  };

  int n;                      // 顶点总数
  int S, T;                   // 源点和汇点
  int maxflow;                // 最大流结果
  vector<vector<Edge>> graph; // 图的邻接表
  vector<int> dep;            // 深度数组（BFS分层）
  vector<int> cur;            // 当前弧优化数组

  // 构造函数：初始化最大流算法
  MaxFlow(int num_nodes, int source, int sink)
      : n(num_nodes), S(source), T(sink), maxflow(0) {
    graph.resize(n + 1);
    dep.resize(n + 1);
    cur.resize(n + 1);
  }

  void addedge(int u, int v, ll w) {
    // 添加正向边：u->v，容量w
    graph[u].push_back({v, w, 0, (int)graph[v].size()});
    // 添加反向边：v->u，容量0
    graph[v].push_back({u, 0, 0, (int)graph[u].size() - 1});
  }

  bool bfs() {
    queue<int> q;
    fill(dep.begin(), dep.end(), 0);

    dep[S] = 1;
    q.push(S);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (auto e : graph[u]) {
        int v = e.v;
        // 未访问过且有余量
        if (!dep[v] && e.cap > e.flow) {
          dep[v] = dep[u] + 1;
          q.push(v);
        }
      }
    }
    return dep[T]; // 返回汇点是否可达
  }

  int dfs(int u, int flow) {
    if (u == T || flow == 0)
      return flow;

    int ret = 0;
    for (int &i = cur[u]; i < graph[u].size(); i++) {
      Edge &e = graph[u][i];
      int v = e.v;
      // 按层次图移动且有余量
      if (dep[v] == dep[u] + 1 && e.cap > e.flow) {
        int d = dfs(v, min(flow - ret, e.cap - e.flow));
        if (d > 0) {
          ret += d;
          e.flow += d; // 更新正向边流量
          // 更新反向边流量
          graph[v][e.rev].flow -= d;
          if (ret == flow)
            break;
        }
      }
    }
    return ret;
  }

  void dinic() {
    maxflow = 0;
    while (bfs()) {
      fill(cur.begin(), cur.end(), 0); // 重置当前弧
      maxflow += dfs(S, INF);
    }
  }
};