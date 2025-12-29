#include <bits/stdc++.h>
using namespace std;
#define int long long
void solve() {
  string s, t;
  cin >> t >> s;
  vector<pair<int, int>> bfe(1e6 + 10);
  int ans{};
  int j{};
  vector<pair<int, int>> shang;
  for (int i = 0; i < s.size(); i++) {
    if (s[i] == t[j]) {
      j++;
    } else {
      //   bfe[i - 1] = j - 1;
      shang.push_back({i - 1, j - 1});
      j = 0;
    }
    cout << i << ' ' << j << '\n';
    if (j == t.size()) {
      ans++;
      cout << i << " " << i - t.size() << '\n';
      string ww = s.substr(0, i - t.size()) + s.substr(i + 1, s.size());
      cout << ww << '\n';
      s = ww;
      i -= t.size();
      if (shang.size() != 0) {
        auto [w, e] = shang[shang.size() - 1];
        if (w == i) {
          j = e + 1;
        }
      }
    }
  }
  cout << ans << " " << s << '\n';
}
#undef int
int main() {
  int T = 1;
  // cin >> T;
  while (T--) {
    solve();
  }
}