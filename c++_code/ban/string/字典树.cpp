#include <bits/stdc++.h>
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
int t[3000001][110], idx = 0;
int cnt[3000001];

int getnum(char s) {
	if (s >= 'a' && s <= 'z') {
		return s - 'a' + 1;
	} else if (s >= 'A' && s <= 'Z') {
		return s - 'A' + 28;
	} else {
		return s - '0' + 56;
	}
}

void insert(string str) {
	int p = 0, len = str.length();
	for (int i = 0; i < len; i++) {
		int c = getnum(str[i]);
		if (!t[p][c])
			t[p][c] = ++idx;
		p = t[p][c];
		cnt[p]++;
	}
}

int find(string str) {
	int p = 0, len = str.length();
	for (int i = 0; i < len; i++) {
		int c = getnum(str[i]);
		if (!t[p][c])
			return 0;
		p = t[p][c];
	}
	return cnt[p];
}

void slove() {
	int n, q;
	cin >> n >> q;
	idx = 0;
	for (int i = 1; i <= n; i++) {
		string ss;
		cin >> ss;
		insert(ss);
	}
	while (q--) {
		string sub;
		cin >> sub;
		cout << find(sub) << endl;
	}
	for (int i = 0; i <= idx; i++) {
		cnt[i] = 0;
		for (int j = 0; j <= 100; j++) {
			t[i][j] = 0;
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int T = 1;
	cin >> T;
	while (T--) {
		slove();
	}
}