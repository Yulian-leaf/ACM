#include <bits/stdc++.h>
using namespace std;
#define int long long
void solve() {
  int n, k;
  cin >> n >> k;
  int minn = 1e5;
  int cost{}, ans{};
  vector<pair<int, int>> cha;
  for (int i = 1; i <= n; i++) {
    int t, p, c;
    cin >> t >> p >> c;
    if (t < minn) {
      minn = t;
    }
    if (t > minn && k > 0) {

      cha.push_back({t * p - minn * p, -c});
    }
    ans += t * p;
  }
  sort(cha.begin(), cha.end());
  for (int i = cha.size() - 1; i >= 0; i--) {
    k--;
    if (k < 0)
      break;
    cost -= cha[i].second;
    ans -= cha[i].first;
  }
  cout << ans << " " << cost << '\n';
}
#undef int
int main() {
  int T = 1;
  // cin >> T;
  while (T--) {
    solve();
  }
}