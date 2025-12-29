#include <bits/stdc++.h>
using namespace std;
#define Endl "\n"
#define INF 0x3f3f3f3f
#define PI 3.14159265358979323846 // 20f
#define MOD 998244353
// #define MOD 1e9+7
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;

#undef DEBUG // open or close
#ifdef DEBUG
#define debug(format, ...) printf(format, ##__VA_ARGS__)
#else
#define debug(format, ...)
#endif

#define int long long

void work() {
  int n;
  cin >> n;
  string s;
  cin >> s;
  int cnt = 0;
  for (int i = 0; i < n - 1; i++)
    if (s[i] == '1' && s[i + 1] == '1')
      cnt++;
  if (s[0] == '1')
    cnt++;
  if (s[n - 1] == '1')
    cnt++;
  if (cnt >= 2 || (cnt == 1 && n % 2 == 1))
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
  cin >> T;
  while (T--) {
    work();
  }
}