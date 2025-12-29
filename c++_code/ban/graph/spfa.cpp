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
const ll N = 1000000;
int dis[N];
int vis[N];
int cnt[N];

struct edge {
	int w, v;
};
vector<vector<pair<int, int> > >e(N);
queue<int>q;
int s, d;
int n, m;

bool spfa() {
	memset(dis, 0, sizeof(dis));
	q.push(s);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		vis[u] = 0;
		for (auto [w, v] : e[u]) {
			if (dis[v] > dis[u] + w) {
				dis[v] = dis[u] + w;
			}
			cnt[v] = cnt[u] + 1;
			if (cnt[v] >= n)
				return 0;
			if (vis[v] == 0) {
				vis[v] = 1;
				q.push(v);
			}

		}
	}
	return 1;
}

void solve() {

	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		e[u].push_back({v, w});
		e[v].push_back({u, w});
		/*e[u].v = v;
		e[u].w = w;
		e[v].v = u;
		e[v].w = w;*/
	}

	cin >> s >> d;
	spfa();
	return ;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int T = 1;
	//cin >> T;
	while (T--) {
		solve();
	}
	return 0;
}