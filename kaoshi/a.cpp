#include <bits/stdc++.h>
using namespace std;
#define int long long
void solve() {
  int a1, b1, a2, b2, b3;
  int n, m;
  cin >> n >> m;

  cin >> a1 >> a2 >> b1 >> b2 >> b3;
  map<int, map<int, int>> mp;
  map<int, map<int, int>> vis;
  for (int i = 1; i <= n; i++) {
    int d, op;
    cin >> d >> op;
    mp[d][op]++;
  }
  for (int i = 1; i <= m; i++) {
    int t, op;
    cin >> t >> op;
    vis[t][op] = 1;
  }
  int self = 0, qit = 0;
  for (auto [w, e] : mp) {
    for (auto [w2, cnt] : e) {
      int selfa = 0, qita = 0;
      if (w2 == 1) {
        selfa += a1;
        qita -= b1;

      } else if (w2 == 2) {
        qita -= b2;
      } else {
        selfa -= a2;
        qita -= b3;
      }
      selfa *= cnt;
      qita *= cnt;
      if (vis[w][w2] == 1) {
        qita /= 2;
      }
      self += selfa, qit += qita;
      cout << w << " " << self << " " << qit << "\n";
    }
  }
  cout << self << ' ' << qit << '\n';
}
#undef int
int main() {
  int T = 1;
  // cin >> T;
  while (T--) {
    solve();
  }
}