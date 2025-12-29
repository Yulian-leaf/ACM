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
  string s = "\n";
  int na, nb, n;
  cin >> na >> nb;
  // cin >> n;
  getline(cin, s);
  getline(cin, s);
  // getchar();
  cout << s << Endl;
  vector<string> a(na + 10), b(nb + 10);
  for (int i = 1; i <= na; i++)
    cin >> a[i];
  for (int i = 1; i <= nb; i++)
    cin >> b[i];
  int ansa = 0, ansb = 0;
  for (int i = 0; i < s.size(); i++) {
    for (int j = 1; j <= na; j++) {
      int fla = 1;
      for (int w = 0; w < a[j].size(); w++) {
        if (a[j][w] != s[i + w]) {
          fla = 0;
          break;
        }
      }
      ansa += fla;
    }
    for (int j = 1; j <= nb; j++) {
      int fla = 1;
      for (int w = 0; w < b[j].size(); w++) {
        if (b[j][w] != s[i + w]) {
          fla = 0;
          break;
        }
      }
      ansb += fla;
    }
  }
  cout << ansa << " " << ansb << endl;
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