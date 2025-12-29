#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
const int N = 50005;
const int M = 50005;

struct edge {
	int v, w, fail;
	edge() {}
	edge(int _v, int _w, int _fail) {
		v = _v;
		w = _w;
		fail = _fail;
	}
} e[M];
int head[N], len;

void init() {
	memset(head, -1, sizeof(head));
	len = 0;
}

void add(int u, int v, int w) {
	e[len] = edge(v, w, head[u]);
	head[u] = len++;
}
int n, m;
int dis[N], in[N];
bool vis[N];

bool spfa(int u) {
	memset(vis, false, sizeof(vis));
	vis[u] = true;
	memset(dis, -1, sizeof(dis));
	dis[u] = 0;
	memset(in, 0, sizeof in);
	in[u] = 1;
	queue<int> q;
	q.push(u);
	while (!q.empty()) {
		u = q.front();
		q.pop();
		vis[u] = false;
		for (int j = head[u]; j != 0; j = e[j].fail) {
			int v = e[j].v;
			int w = e[j].w;
			if (dis[v] < dis[u] + w) {
				dis[v] = dis[u] + w;
				if (!vis[v]) {
					q.push(v);
					vis[v] = true;
					++in[v];
					if (in[v] > n + 1)
						return true;
				}
			}
		}
	}
	return false;
}

int main() {
	init();
	int u, v, w, op;
	cin >> n >> m;
	while (m--) {
		cin >> u >> v >> w;
		add(u, v, -w);
	}
	for (int i = 1; i <= n; ++i)
		add(0, i, 0);
	if (spfa(0))
		cout << "NO" << endl;
	else
		for (int i = 1; i <= n; ++i)
			cout << dis[i] << " ";
	return 0;
}