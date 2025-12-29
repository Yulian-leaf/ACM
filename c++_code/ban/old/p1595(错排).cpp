#include <iostream>
#define int long long
using namespace std;

const int N = 52;
int d[N];

signed main() {
	int n;
	cin >> n;
	d[1] = 0;
	d[2] = 1;
	d[3] = 2;
	for (int i = 4; i <= n; i++) {
		d[i] = (i - 1) * (d[i - 1] + d[i - 2]);
	}
	cout << d[n];
}