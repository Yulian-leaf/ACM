#include <iostream>
#include <algorithm>
using namespace std;

struct edge {
	int u, v, w;
} s[520520];

bool cmp(edge a, edge b) {
	return a.w < b.w;
}
int n, m;
int f[5205];

int find(int x) {
	if (f[x] == x)
		return x;
	else
		return f[x] = find(f[x]);
}

void join(int a, int b) {
	int f1 = f[a], f2 = f[b];
	if (f1 != f2) {
		f[f1] = f2;
		/*
		*/
	}
}

int Kruskal() {
	sort(s + 1, s + m + 1, cmp);
	int res = 0, cnt = 0;
	for (int i = 1; i <= m; i++) {
		int a = s[i].u, b = s[i].v;
		int f1 = find(a), f2 = find(b);
		if (f1 != f2) {
			f[f1] = f2;
			res += s[i].w;
			cnt++;
		}
	}
	if (cnt < n - 1)
		return -1;
	else
		return res;
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		f[i] = i;
	for (int i = 1; i <= m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		s[i] = {a, b, c};
	}
	int ans = Kruskal();
	if (ans == -1) {
		cout << "orz";
	} else {
		cout << ans;
	}
	return 0;
}