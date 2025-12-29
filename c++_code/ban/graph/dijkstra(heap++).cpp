#include <bits/stdc++.h>
#define Endl "\n"
typedef long long ll;
typedef unsigned long long ull;
using namespace std;

inline void read(int &a) {
  int s = 0, w = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-')
      w = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    s = s * 10 + ch - '0';
    ch = getchar();
  }
  a = s * w;
}
const int M = 1000010;

struct edge {
  int to, dis, nxt;
};
edge e[M];
int head[M], dis[M], cnt;
int vis[M];
int n, m, s;

struct node {
  int dis;
  int pos;
  bool operator<(const node &x) const { return x.dis < dis; }
};

void add(int u, int v, int d) {
  cnt++;
  e[cnt].dis = d;
  e[cnt].to = v;
  e[cnt].nxt = head[u];
  head[u] = cnt;
}
priority_queue<node> q;

void dijkstra() {
  dis[s] = 0;
  q.push((node){0, s});
  while (!q.empty()) {
    node yul = q.top();
    int x = yul.pos;
    q.pop();
    if (vis[x] != 0)
      continue;
    vis[x] = 1;
    for (int i = head[x]; i != 0; i = e[i].nxt) {
      int y = e[i].to;
      if (dis[y] > dis[x] + e[i].dis) {
        dis[y] = dis[x] + e[i].dis;
        if (vis[y] == 0) {
          q.push((node){dis[y], y});
        }
      }
    }
  }
}
// Dijkstra 算法
vector<int> dis;
void dijkstra(int start, vector<vector<pair<int, int>>> &graph,
              vector<int> &dist) {
  // 初始化最短距离数组
  dist.assign(MAX, INF);
  dist[start] = 0;

  // 使用优先队列（最小堆）
  priority_queue<pair<int, int>, vector<pair<int, int>>,
                 greater<pair<int, int>>>
      pq;
  pq.push({0, start});

  while (!pq.empty()) {
    int u = pq.top().second;
    int d = pq.top().first;
    pq.pop();

    // 如果当前距离大于已经找到的最短距离，跳过
    if (d > dist[u])
      continue;

    // 遍历相邻的点
    for (auto &edge : graph[u]) {
      int v = edge.first;
      int weight = edge.second;

      // 如果通过 u 到 v 的路径更短，更新最短距离
      if (dist[u] + weight < dist[v]) {
        dist[v] = dist[u] + weight;
        pq.push({dist[v], v});
      }
    }
  }
}
void solve() {
  cin >> n >> m >> s;
  while (m--) {
    int u, v, w;
    cin >> u >> v >> w;
    add(u, v, w);
  }
  s = 1;
  for (int i = 1; i <= n; i++)
    dis[i] = 2e9;
  dijkstra();
  for (int i = 1; i <= n; i++)
    cout << dis[i] << " ";
  cout << Endl;
  return;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int T = 1;
  // cin >> T;
  while (T--) {
    solve();
  }
  return 0;
}