#include <cmath>
#include <iostream>
using namespace std;
const int N = 1e5 + 10;
int a[N], sum[N], bel[N];
int st[N], ed[N];

int main() {
  int n, m;
  cin >> n >> m;
  int sq = sqrt(n);
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= sq; i++) {
    st[i] = (i - 1) * (n / sq) + 1;
    ed[i] = i * (n / sq);
    if (i == sq)
      ed[i] = n;
    for (int j = st[i]; j <= ed[i]; j++) {
      bel[j] = i;
      sum[i] += a[j];
    }
  }
  while (m--) {
    int opt, x, y;
    int ans = 0;
    cin >> opt >> x >> y;
    if (opt == 2) {
      a[x] += y;
      sum[bel[x]] += y;
    } else {
      if (bel[x] == bel[y]) {
        for (int i = x; i <= y; i++) {
          ans += a[i];
        }
      } else {
        for (int i = x; i <= ed[bel[x]]; i++) {
          ans += a[i];
        }
        for (int i = bel[x] + 1; i < bel[y]; i++) {
          ans += sum[i];
        }
        for (int i = st[bel[y]]; i <= y; i++) {
          ans += a[i];
        }
      }
      cout << ans << endl;
    }
  }
  return 0;
}