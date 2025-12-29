#include <iostream>
typedef long long ll;
using namespace std;
long long quick_mul(long long x, long long y, long long mod) {
  long long ans = 0;
  while (y != 0) {
    if (y & 1 == 1)
      ans += x, ans %= mod;
    x = x + x, x %= mod;
    y >>= 1;
  }
  return ans;
}

// base**power
ll qp(ll base, ll power, ll mod) {
  ll result = 1;
  while (power > 0) {
    if (power & 1) {
      result *= base;
      /*
      result=quick_mul(result,base,mod);
      */
      result %= mod;
    }

    power >>= 1;
    base *= base;
    /*
    base=quick_mul(base,base,mod);
    */
    base %= mod;
  }
  return result;
}

int main() {}