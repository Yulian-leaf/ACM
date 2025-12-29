#include <cstring>
#include <iostream>
using namespace std;
bool a[520520520];
int prime[520520];

void yulprime(int n) {
  int cnt = 0;
  a[0] = a[1] = 1;
  memset(a, 0, sizeof(bool) * (n + 1));
  for (int i = 2; i <= n / i; i++) {
    if (a[i] == 0) {
      for (int j = i * i; j <= n; j += i) {
        a[j] = 1;
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    if (a[i] == 0)
      prime[cnt++] = i;
  }
}
bool isprime(int x) {
  if (x == 1 || x == 0)
    return 0;
  for (int i = 2; i <= x / i; i++) {
    if (x % i == 0)
      return 0;
  }
  return 1;
}
int main() {
  int T;
  cin >> T;
  // yulprime(1000000);
  while (T--) {
    int x;
    cin >> x;
    if (isprime(x))
      cout << "YES" << endl;
    else
      cout << "NO" << endl;
  }
}