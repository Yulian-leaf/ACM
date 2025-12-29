
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
  int n;
  cin >> n;
  int maxxa = -0x3f3f3f3f, minna = 0x3f3f3f3f, maxxb = -0x3f3f3f3f,
      minnb = 0x3f3f3f3f;
  for (int i = 1; i <= n; i++) {
    int x, y;
    cin >> x >> y;
    maxxa = max(maxxa, x - y); //  4
    minna = min(minna, x - y); //  2
    maxxb = max(maxxb, x + y); //  1
    minnb = min(minnb, x + y); //  3
  }
  cout << max(maxxa - minna, maxxb - minnb) << endl;
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