#include <iostream>
typedef long long ull;
using namespace std;
ull a[12], b[12];

int exgcd(ull a, ull b, ull &x, ull &y) {
	if (!b) {
		x = 1, y = 0;
		return a;
	}
	ull d = exgcd(b, a % b, y, x);
	y -= a / b * x;
	return d;
}

ull crt(ull n) {
	ull num = 1, ans = 0;
	for (int i = 1; i <= n; i++)
		num *= a[i];
	for (int i = 1; i <= n; i++) {
		ull t = num / a[i], x, y;
		exgcd(t, a[i], x, y);
		ans += b[i] * t * x;
	}
	return (ans % num + num) % num;
}

int main() {
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i] >> b[i];
	}
	cout << crt(n);
}