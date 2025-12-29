#include <bits/stdc++.h>
using namespace std;
void solve() {
  int n, m;
  double k;
  cin >> n >> m >> k;
  vector<array<int, 4>> a(n + 10);
  for (int i = 1; i <= n; i++) {
    int v, p, h;
    cin >> v >> p >> h;
    a[i] = {v, -p, -h, i};
  }
  vector<pair<int, double>> f(m + 10);
  priority_queue<tuple<int, double, int>> f2;
  for (int i = 1; i <= m; i++) {
    int p, h;
    cin >> p >> h;
    f[i] = {p, h * 1.0};
    f2.push({p, h * 1.0, i});
  }
  sort(a.begin() + 1, a.begin() + n + 1, greater());

  vector<int> ans(n + 10);
  for (int we = 1; we <= n; we++) {
    auto [v, p, h, i] = a[we];
    p = -p, h = -h;
    // cout << "I: " << i << " v: " << v << " p: " << p << " h: " << h << "\n";
    vector<tuple<int, double, int>> cun;
    for (int w = 1; w <= m; w++) {
      auto [P, H, j] = f2.top();
      H = f[j].second;
      f2.pop();
      // cout << "J: " << j << "P: " << P << " H: " << H << '\n';
      if (P >= p && H >= h) {
        if (j != 1) {
          if (f[j - 1].second < k * double(h)) {
            cun.push_back({P, H, j});
            continue;
          }
        }
        if (j != m) {
          if (f[j + 1].second < k * double(h)) {
            cun.push_back({P, H, j});
            continue;
          }
        }
        f[j].first -= p;
        f[j].second -= h;
        if (j != 1)
          f[j - 1].second -= k * h;
        if (j != n)
          f[j + 1].second -= k * h;
        ans[i] = j;
        cun.push_back({P - p, H - h, j});
        break;
      } else {
        cun.push_back({P, H, j});
      }
    }
    for (int kk = 0; kk < cun.size(); kk++) {
      auto [P, H, j] = cun[kk];
      // cout << "     J: " << j << "P: " << P << " H: " << H << " fs"
      //      << f[j].second << '\n';
      f2.push({P, f[j].second, j});
    }
  }
  for (int i = 1; i <= n; i++)
    cout << ans[i] << " ";
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie();
  solve();
}