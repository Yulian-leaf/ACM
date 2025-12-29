#include <iostream>
#include <algorithm>
using namespace std;
int n, a[100005];

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	for (int i = 1; i <= n; i++) {
		int x = a[i];
		int j = i - 1;
		while (j >= 0 and a[j] > x) {
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = x;
	}
	for (int i = 1; i <= n; i++) {
		cout << a[i] << ' ';
	}
	return 0;
}