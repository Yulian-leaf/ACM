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
const int mo = 998244353;
const int N = 1e9 + 10;

const int p = 998244353;
inline void add(int &a, int b) { a = a + b - (a + b >= p ? p : 0); }
inline void mul(int &a, int b) { a = 1ll * a * b % p; }
inline int get_sum(int a, int b) { return a + b - (a + b >= p ? p : 0); }
inline int get_product(int a, int b) { return 1ll * a * b % p; }
inline int get_power(int a, int n) {
  int res = 1;
  a %= p;
  while (n) {
    res = (n & 1) ? get_product(res, a) : res;
    mul(a, a);
    n >>= 1;
  }
  return res;
}
inline int get_inv(int x) { return get_power(x, p - 2); }
const int max_k = 3e6;
bool mark_prime[max_k];
int prime[max_k], cnt;
int power[max_k];
int x[max_k], y[max_k];
int inv[max_k], inv_fac[max_k];
void init(int k) {
  power[1] = 1;
  for (int i = 2; i <= k + 1; ++i) {
    if (!mark_prime[i]) {
      prime[++cnt] = i;
      power[i] = get_power(i, k);
    }
    for (int j = 1; j <= cnt && 1ll * i * prime[j] <= k + 1; ++j) {
      mark_prime[i * prime[j]] = true;
      power[i * prime[j]] = get_product(power[i], power[prime[j]]);
      if (i % prime[j] == 0)
        break;
    }
  }
  x[0] = y[0] = 0;
  for (int i = 1; i <= k + 1; ++i) {
    x[i] = i;
    y[i] = get_sum(y[i - 1], power[i]);
  }
  inv_fac[0] = 1;
  inv[1] = inv_fac[1] = 1;
  for (int i = 2; i <= k + 1; ++i) {
    inv[i] = get_product(p - p / i, inv[p % i]);
    inv_fac[i] = get_product(inv_fac[i - 1], inv[i]);
  }
}
int pre[max_k], suf[max_k];
int get(int n, int k) {
  if (n <= k + 1)
    return y[n];
  pre[0] = n;
  for (int i = 1; i <= k + 1; ++i)
    pre[i] = get_product(pre[i - 1], n - i);
  suf[k + 1] = n - k - 1;
  for (int i = k; i >= 0; --i)
    suf[i] = get_product(suf[i + 1], n - i);
  int res = 0;
  for (int i = 0; i <= k + 1; ++i) {
    int now = get_product(y[i], get_product(inv_fac[i], inv_fac[k + 1 - i]));
    if ((k + 1 - i) & 1)
      now = get_sum(0, p - now);
    if (i > 0)
      mul(now, pre[i - 1]);
    if (i <= k)
      mul(now, suf[i + 1]);
    add(now, p);
    add(res, now);
  }
  return res;
}
vector<int> bsm(3e6);
void init2(int m, int n) {
  bsm[0] = 1;
  for (int i = 1; i <= m; i++) {
    bsm[i] = bsm[i - 1] * n % mo;
  }
}
void work() {
  int n, m;
  cin >> n >> m;

  init2(n, m);
  int ans = 0;
  // cout << get(3, 2) << Endl;
  for (int i = 1; i <= n; i++) {
    init(i);
    ans = (ans + bsm[n - i] * get(m, i) % mo * (n - i + 1) % mo) % mo;
    // cout << i << ": " << ans << Endl;
  }
  cout << ans << Endl;
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