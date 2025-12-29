#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
const int N = 1e6 + 10, M = 1e8 + 10;
bool a[M];
int prime[N];

void yulprime(int n) {
  int cnt = 0;
  a[0] = a[1] = 1;
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
// 欧式筛法求小于等于 n 的所有质数
std::vector<int> eulerSieve(int n) {
  std::vector<bool> isPrime(n + 1, true);
  std::vector<int> primes;
  for (int i = 2; i <= n; ++i) {
    if (isPrime[i]) {
      primes.push_back(i);
    }
    for (int j = 0; j < primes.size() && i * primes[j] <= n; ++j) {
      isPrime[i * primes[j]] = false;
      if (i % primes[j] == 0) {
        break;
      }
    }
  }
  return primes;
}
int main() {
  int n, q;
  cin >> n >> q;
  yulprime(n);
  while (q--) {
    int x;
    cin >> x;
    cout << prime[x] << endl;
  }
  return 0;
}