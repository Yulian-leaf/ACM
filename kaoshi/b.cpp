#include <bits/stdc++.h>
using namespace std;
#define int long long
void solve() {
  int n, m, q;
  cin >> n >> m >> q;
  vector<string> mp(n + 10);
  for (int i = 1; i <= n; i++) {
    string t = " ";
    for (int j = 1; j <= m; j++) {
      t = t + ".";
    }
    mp[i] = t;
  }
  auto check = [&](vector<string> xiao, vector<string> da, int a, int b,
                   int basei, int basej) {
    for (int i = 1; i <= a; i++) {
      for (int j = 1; j <= b; j++) {
        int i2 = basei + i - 1;
        int j2 = basej + j - 1;
        int cnt = 0;
        if (i2 > n || j2 > m) {
          if (xiao[i][j] == '*')
            return 0;
          continue;
        }
        if (da[i2][j2] == '*')
          cnt++;
        if (xiao[i][j] == '*')
          cnt++;
        // cout << i << ' ' << j << '\n' << i2 << " " << j2 << " " << cnt <<
        // "\n";
        if (cnt == 2)
          return 0;
      }
    }
    return 1;
  };
  // auto fugai = [&](vector<string> xiao, vector<string> da, int a, int b,
  //                  int basei, int basej) {

  //   pair<int, int> res = {resx, resy};
  //   pair<pair<int, int>, vector<string>> rres = {res, da};
  //   return rres;
  // };
  auto show = [&] {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        cout << mp[i][j];
      }
      cout << "\n";
    }
  };
  auto show2 = [&](vector<string> sss, int nn, int mm) {
    for (int i = 1; i <= nn; i++) {
      for (int j = 1; j <= mm; j++) {
        cout << sss[i][j];
      }
      cout << "\n";
    }
  };
  while (q--) {
    cout << "Q: " << q << "\n";
    int sizn, sizm;
    cin >> sizn >> sizm;
    vector<string> tu(sizn + 10);
    for (int i = 1; i <= sizn; i++) {
      cin >> tu[i];
      tu[i] = " " + tu[i];
    }
    int fla = 0;
    while (fla == 0 && sizn >= 1) {
      for (int i = 1; i <= sizm; i++) {
        if (tu[1][i] == '*')
          fla = 1;
      }
      if (fla == 0) {
        for (int i = 1; i <= sizn; i++) {
          for (int j = 1; j <= sizm; j++) {
            tu[i][j] = tu[i + 1][j];
          }
        }
        sizn--;
      }
    }
    fla = 0;
    while (fla == 0 && sizm >= 1) {
      for (int i = 1; i <= sizn; i++) {
        if (tu[i][1] == '*')
          fla = 1;
      }
      if (fla == 0) {
        for (int i = 1; i <= sizn; i++) {
          for (int j = 1; j <= sizm; j++) {
            tu[i][j] = tu[i][j + 1];
          }
        }
        sizm--;
      }
    }
    fla = 0;
    int resx = 0, resy = 0;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        if (check(tu, mp, sizn, sizm, i, j)) {
          fla = 1;
          cout << i << " " << j << '\n';
          cout << "before" << "\n";
          show();
          for (int ii = 1; ii <= sizn; ii++) {
            for (int jj = 1; jj <= sizm; jj++) {
              int i2 = i + ii - 1;
              int j2 = j + jj - 1;
              // cout << ii << " " << jj << " " << tu[ii][jj] << resx << ' '
              //  << resy << '\n';
              if (tu[ii][jj] == '*') {
                if (resx == 0 && resy == 0) {
                  resx = i2, resy = j2;
                  // cout << resx << " " << resy << '\n';
                }
                mp[i2][j2] = '*';
              }
            }
          }
          cout << "end" << '\n';
          show();
        }
        if (fla == 1)
          break;
      }
      if (fla == 1)
        break;
    }
    if (fla == 1)
      cout << resx << " " << resy << "\n";
    else {
      cout << -1 << " " << -1 << '\n';
    }
    // show();
  }
}
#undef int
int main() {
  int T = 1;
  // cin >> T;
  while (T--) {
    solve();
  }
}