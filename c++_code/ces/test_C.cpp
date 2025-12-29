#include <bits/stdc++.h>
using namespace std;
void solve() {
  int n, m;
  double k;
  cin >> n >> m >> k;
  vector<tuple<int, int, int>> a(n + 10);
  for (int i = 1; i <= n; i++) {
    int v, p, h;
    cin >> v >> p >> h;
    a[i] = {v, -p, -h};
  }
  vector<pair<int, double>> f(m + 10), f2(m + 10);
  for (int i = 1; i <= m; i++) {
    int p, h;
    cin >> p >> h;
    f[i] = {p, h};
    f2[i] = {p, h};
  }
  sort(a.begin() + 1, a.begin() + n + 1, greater());
  vector<int> ans1(n + 10), ans2(n + 10);
  int res1, res2;
  for (int i = 1; i <= n; i++) {
    auto [v, p, h] = a[i];
    p = -p, h = -h;
    // cout << "I: " << i << " v: " << v << " p: " << p << " h: " << h << "\n";
    for (int j = 1; j <= m; j++) {
      auto [P, H] = f[j];
      // cout << "J: " << j << "P: " << P << " H: " << H << '\n';

      if (P > p && H > h) {
        if (j != 1) {
          if (f[j - 1].second < k * double(h)) {
            // cout << j - 1 << " " << f[j - 1].second << " " << k * double(h)
            //      << "  111111\n";
            continue;
          }
        }
        if (j != m) {
          if (f[j + 1].second < k * double(h)) {
            // cout << f[j + 1].second << " " << k * double(h) << " 222222\n";
            continue;
          }
        }
        f[j].first -= p;
        f[j].second -= h;
        if (j != 1)
          f[j - 1].second -= k * h;
        if (j != n)
          f[j + 1].second -= k * h;
        ans1[i] = j;
        res1 += v;
        break;
      }
    }
  }

  for (int i = 1; i <= n; i++) {
    auto [v, p, h] = a[i];
    p = -p, h = -h;
    // cout << "I: " << i << " v: " << v << " p: " << p << " h: " << h << "\n";
    for (int j = 1; j <= m; j++) {
      auto [P, H] = f2[j];
      // cout << "J: " << j << "P: " << P << " H: " << H << '\n';

      if (P > p && H > h) {
        if (j != 1) {
          if (f2[j - 1].second < k * double(h)) {
            // cout << j - 1 << " " << f[j - 1].second << " " << k * double(h)
            //      << "  111111\n";
            continue;
          }
        }
        if (j != m) {
          if (f2[j + 1].second < k * double(h)) {
            // cout << f[j + 1].second << " " << k * double(h) << " 222222\n";
            continue;
          }
        }
        f2[j].first -= p;
        f2[j].second -= h;
        if (j != 1)
          f2[j - 1].second -= k * h;
        if (j != n)
          f2[j + 1].second -= k * h;
        ans2[i] = j;
        res2 += v;
        break;
      }
    }
  }
  if (res1 > res2)
    for (int i = 1; i <= n; i++)
      cout << ans1[i] << " ";
  else
    for (int i = 1; i <= n; i++)
      cout << ans2[i] << " ";
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie();
  solve();
}