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
int f[100000];
int find(int x) {
  if (f[x] == x)
    return x;
  else
    return f[x] = find(f[x]);
}
void join(int x, int y) {
  int f1 = find(x), f2 = find(y);
  if (f1 != f2) {
    f[f1] = f2;
  }
}
void work() {
  int cep = 0;
  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    f[i] = i;
  }
  while (m--) {
    int x, y;
    cin >> x >> y;
    for (int i = 1; i <= n; i++) {
      cep += x + y;
    }
    join(x, y);
  }
  for (int i = 1; i <= n; i++) {
    f[i] = find(f[i]);
  }
  if (f[1] == f[n])
    cout << "YES" << Endl;
  else
    cout << "NO" << Endl;
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