#include <bits/stdc++.h>
using namespace std;
#define Endl "\n"
#define INF 0x3f3f3f3f
#define PI 3.14159265358979323846 // 20f
const int MOD = 998244353;
// const int MOD = 1e9 + 7;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
#define int long long

void work() {
  int n, w;
  cin >> n >> w;
  while (n--) {
    int op, a, b;
    cin >> op >> a >> b;
    if (op == 0) {
      w += b;
    } else if (op == 1) {
      if (b > a && w > a) {
        w += b - a;
      }
    } else {
      if (w <= a) {
        cout << "NO" << Endl;
        return;
      }
      w -= a;
      w += b;
    }
  }
  int s;
  cin >> s;
  if (w > s) {
    cout << "YES" << Endl;
  } else {
    cout << "NO" << Endl;
  }
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