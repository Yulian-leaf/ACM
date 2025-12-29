#include <iostream>
#include <cstring>
using namespace std;
int a[520520], G[5205][5205], D[5205][5205], path[5205][5205];
int n, m;

void Floyd() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			D[i][j] = G[i][j];
			path[i][j] = 1;
		}
	}
	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (D[i][k] + D[k][j] < D[i][j]) {
					D[i][j] = D[i][k] + D[k][j];
					path[i][j] = k;
				}
			}
		}
	}
}

void show() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cout << D[i][j] << " ";
		}
		cout << endl;
	}
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		cin >> a[i];
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> G[i][j];
		}
	}
	Floyd();
	int ans = 0;
	for (int i = 2; i <= m; i++) {
		ans += D[a[i - 1]][a[i]];
	}
	cout << ans << endl;
	return 0;
}