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

struct node {
	ll w, h;
	node() {
		w = 0, h = 0;
	}
	node(ll w, ll h): w(w), h(h) {}
	bool operator <(const node &a)const {
		return a.w == w ? h > a.h : w > a.w;
	}
};
priority_queue<node >q;
vector<pair<int, int> >sd;



void solve() {
	ll n, k;
	ll ans = 0;
	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		ll w;
		cin >> w;
		q.push({w, 1});
	}
	while ((q.size() - 1) % (k - 1) != 0)
		q.push({0, 1});
	while (q.size() >= k) {
		ll h = -1;
		ll w = 0;
		for (int i = 1; i <= k; ++i) {
			node t = q.top();
			//cout << t.h << " " << t.w << Endl;
			q.pop();
			h = max(h, t.h);
			w += t.w;
		}
		//cout << ans << " ";
		ans += w;
		q.push({w, h + 1});
	}
	//cout << Endl;
	cout << ans << Endl << q.top().h - 1 << Endl;
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