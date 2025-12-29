#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, a[100001];

void pop_sort() {
	for (int i = 1; i <= n; i++)
		for (int j = 1; j < n; j++)
			if (a[j] > a[j + 1])
				swap(a[j], a[j + 1]);
}

signed main() {
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	pop_sort();
	for (int i = 1; i <= n; i++)
		cout << a[i] << ' ';
	return 0;
}