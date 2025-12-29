#include <iostream>
using namespace std;
int s[520025], temp[520025];
long long ans;

void merge(int a, int b) {
	if (a >= b)
		return ;
	int mid = (a + b) / 2;
	int c = 0;
	merge(a, mid);
	merge(mid + 1, b);
	int i = a;
	int j = mid + 1;
	while (i <= mid && j <= b) {
		if (s[i] <= s[j]) {
			temp[++c] = s[i++];
		} else {
			temp[++c] = s[j++];
			ans += mid - i + 1;
		}
	}
	while (i <= mid)
		temp[++c] = s[i++];
	while (j <= b)
		temp[++c] = s[j++];
	for (int i = 1; i <= c; i++) {
		s[a++] = temp[i];
	}
}

int main() {
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> s[i];
	}
	merge(1, n);
	cout << ans;
	/*	for (int i = 1; i <= n; i++) {
			cout << s[i] << " ";
		}
	*/	return 0;
}