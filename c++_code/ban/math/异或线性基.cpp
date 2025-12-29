#include <bits/stdc++.h>
using namespace std;

struct XorBasis {
  static const int LOG = 61;
  long long d[LOG]{};
  int r = 0;
  void insert(long long x) {
    for (int i = LOG - 1; i >= 0; --i) {
      if (!(x >> i & 1))
        continue;
      if (!d[i]) {
        d[i] = x;
        ++r;
        return;
      }
      x ^= d[i];
    }
  }

  vector<long long> rebuild() {
    for (int i = 0; i < LOG; ++i)
      if (d[i]) {
        for (int j = i - 1; j >= 0; --j)
          if (d[j] && (d[i] >> j & 1))
            d[i] ^= d[j];
      }
    vector<long long> b;
    for (int i = 0; i < LOG; ++i)
      if (d[i])
        b.push_back(d[i]);
    return b;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int N;
  if (!(cin >> N))
    return 0;
  XorBasis lb;
  for (int i = 0; i < N; ++i) {
    long long x;
    cin >> x;
    lb.insert(x);
  }
  auto b = lb.rebuild();
  int r = (int)b.size();
  if (r == 0) {
    cout << 0 << '\n';
    return 0;
  }
  unsigned long long k = 1ULL << (r - 1);
  long long ans = 0;
  for (int i = 0; i < r; ++i)
    if (k >> i & 1ULL)
      ans ^= b[i];
  cout << ans << '\n';
  return 0;
}
