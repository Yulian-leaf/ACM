#include <bits/stdc++.h>
using namespace std;

int lg[100005], f[100005][24];

void slove() {
  int n, m;
  cin >> n >> m;
  vector<int> lg(n + 10);
  vector<vector<int>> f(n + 10, vector<int>(30));
  for (int i = 2; i <= n; i++)
    lg[i] = lg[i >> 1] + 1;
  for (int i = 1; i <= n; i++)
    cin >> f[i][0];
  for (int j = 1; j <= lg[n]; j++) {
    for (int i = 1; i <= n - (1 << j) + 1; i++) {
      f[i][j] = max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
    }
  }
  while (m--) {
    int l, r;
    cin >> l >> r;
    int le = lg[r - l + 1];
    cout << max(f[l][le], f[r - (1 << le) + 1][le]) << "\n";
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int T = 1;
  // cin >> T;
  while (T--) {
    slove();
  }
  return 0;
}