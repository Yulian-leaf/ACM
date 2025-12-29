#include <bits/stdc++.h>
using namespace std;
int main() {
  int n, w;
  cin >> n >> w;
  while (n--) {
    int op, cost, get;
    cin >> op >> cost >> get;
    if (op == 0) {
      w += get;
    } else if (op == 1) {
      if (get > cost) {
        if (w > cost) {
          w += get - cost;
        }
      }
    } else {
      if (w > cost) {
        w -= cost;
        w += get;
      } else {
        cout << "NO" << endl;
        return 0;
      }
    }
  }
  int hp;
  cin >> hp;
  if (w <= hp) {
    cout << "NO" << endl;
  } else {
    cout << "YES" << endl;
  }
}