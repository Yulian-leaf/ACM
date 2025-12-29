#include <iostream>
using namespace std;
int a[520520], b[520520];
int dp[5205][5205];

int main() {
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	for (int i = 1; i <= n; i++) {
		cin >> b[i];
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (a[i] == b[j]) {
				dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1);
			} else {
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
			}
		}
	}
	cout << dp[n][n];
	return 0;
}