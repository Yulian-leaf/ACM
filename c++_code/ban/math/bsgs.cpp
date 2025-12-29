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
//a**x===b(mod p) --> x
ll bsgs(ll a, ll b, ll mod) {
	map<ll, ll> mp;
	ll cur = 1, t = sqrt(mod) + 1;
	for (int B = 1; B <= t; B++) {
		cur = cur * a % mod;
		mp[b * cur % mod] = B;
	}
	ll now = cur;
	for (int A = 1; A <= t; A++) {
		if (mp[now])
			return (ll)A * t - mp[now];
		now = now * cur % mod;
	}
	return -1;
}

void slove() {
	int a, p, b;
	cin >> p >> b >> a;
	int ans = bsgs(a, b, p);
	if (ans == -1) {
		cout << "no sloution" << Endl;
	} else {
		cout << ans << Endl;
	}
	return ;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int T = 1;
	//cin >> T;
	while (T--) {
		slove();
	}
	return 0;
}
