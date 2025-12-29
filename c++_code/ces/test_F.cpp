#include <bits/stdc++.h>
using namespace std;
#define Endl "\n"
#define INF 0x3f3f3f3f
#define PI 3.14159265358979323846 // 20f
const int MOD = 998244353;
// const int MOD = 1e9 + 7;
typedef long long ll;
typedef unsigned long long ull;
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
#define int ll

void work() {
  int n;
  cin >> n;
  vector<int> a(n + 10);
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  vector<int> d(88);
  auto cal = [&](int x) {
    for (int i = 60; i >= 0; i--) {
      if (!((x >> i) & 1))
        continue;
      if (d[i] == 0) {
        d[i] = x;
        break;
      } else {
        x = d[i] ^ x;
      }
    }
  };
  for (int i = 1; i <= n; i++) {
    cal(a[i]);
  }
  // guifanhui
  for (int i = 60; i >= 0; i--) {
    if (d[i] != 0)
      for (int j = i - 1; j >= 0; j--) {
        if ((d[i] >> j & 1) && d[j] != 0) {
          d[i] ^= d[j];
        }
      }
  }
  vector<int> b;
  for (int i = 0; i <= 60; i++) {
    if (d[i] != 0)
      b.push_back(d[i]);
  }
  int k = b.size();
  int aim = (1 << (k - 1));
  int ans = 0;
  // cout << aim << '\n';
  for (int i = 0; i < k; i++) {
    // cout << b[i] << '\n';
    if ((aim >> i) & 1 == 1) {
      ans += b[i];
    }
  }
  cout << ans << '\n';
}
#undef int
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  // cout << fixed << setprecision(2);
  int T = 1;
  // cin >> T;
  while (T--) {
    work();
  }
}