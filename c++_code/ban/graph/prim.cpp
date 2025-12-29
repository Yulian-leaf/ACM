#include <bits/stdc++.h>
#define Endl "\n"
typedef long long int;
typedef unsigned long long uint;
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
int k, n, m, cnt, sum, ai, bi, ci, head[5005], dis[5005], vis[5005];

struct Edge {
	int v, w, next;
} e[400005];

void add(int u, int v, int w) {
	e[++k].v = v;
	e[k].w = w;
	e[k].next = head[u];
	head[u] = k;
}

typedef pair <int, int> pii;
priority_queue <pii, vector<pii>, greater<pii> > q;

bool prim() {
	dis[1] = 0;
	q.push(make_pair(0, 1));
	while (!q.empty() && cnt < n) {
		int d = q.top().first, u = q.top().second;
		q.pop();
		if (vis[u])
			continue;
		cnt++;
		sum += d;
		vis[u] = 1;
		for (int i = head[u]; i != -1; i = e[i].next)
			if (e[i].w < dis[e[i].v])
				dis[e[i].v] = e[i].w, q.push(make_pair(dis[e[i].v], e[i].v));
	}
	if (cnt != n)
		return 0;
	else
		return 1;
}

void solve() {
	cin >> n >> m;
	memset(dis, 127, sizeof(dis));
	memset(head, -1, sizeof(head));
	for (int i = 1; i <= m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		add(a, b, c);
		add(b, a, c);
	}
	if (!prim()) {
		cout << "orz" << Endl;
		return ;
	}
	cout << sum << Endl;
	return ;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int T = 1;
	//cin >> T;
	//auto h={1};
	while (T--) {
		solve();
	}
	return 0;
}