#include <iostream>
#define ll long long
using namespace std;

ll ExpGcd(ll a, ll b, ll &x, ll &y) {
  ll q, temp;
  if (!b) {
    q = a;
    x = 1;
    y = 0;
  } else {
    q = ExpGcd(b, a % b, x, y);
    temp = x;
    x = y;
    y = temp - (a / b) * y;
  }
  return q;
}

ll Inv(ll a, ll n) {
  ll x, y;
  ExpGcd(a, n, x, y);
  x = (x % n + n) % n;
  return x;
}
int inv[100006];
ll qkpow(ll a, ll p, ll mod) {
  ll t = 1, tt = a % mod;
  while (p) {
    if (p & 1)
      t = t * tt % mod;
    tt = tt * tt % mod;
    p >>= 1;
  }
  return t;
}
ll IInv(ll a, ll mod) { return qkpow(a, mod - 2, mod); }

ll inv2(ll n, ll p) {
  inv[1] = 1;
  cout << 1 << endl;
  for (int i = 2; i <= n; i++) {
    inv[i] = (p - p / i) * inv[p % i] % p;
    cout << inv[i] << endl;
  }
}

int main() {}