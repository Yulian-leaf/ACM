// 分块大法
#include <bits/stdc++.h>
using namespace std;
int sq;
int A[5205205], st[5205205], ed[5205205], siz[5205205];
int mark[5205205], bel[5205205];
vector<int> v[5205];

void update(int b) { // 更新排序后的数组
  for (int i = 0; i <= siz[b]; ++i)
    v[b][i] = A[st[b] + i];
  sort(v[b].begin(), v[b].end());
}

int main() {
  int n, q;
  cin >> n >> q;
  sq = sqrt(n);
  for (int i = 1; i <= n; i++)
    cin >> A[i];
  for (int i = 1; i <= sq; i++) {
    st[i] = n / sq * (i - 1) + 1;
    ed[i] = n / sq * i;
    if (i == sq)
      ed[i] = n;
    for (int j = st[i]; j <= ed[i]; j++) {
      v[i].push_back(A[j]);
      bel[j] = i;
    }
    siz[i] = ed[i] - st[i] + 1;
    sort(v[i].begin(), v[i].end());
  }

  while (q--) {
    char opt;
    int l, r, w;
    cin >> opt >> l >> r >> w;
    if (opt == 1) {
      if (bel[l] == bel[r]) {
        for (int i = l; i <= r; i++) {
          A[i] += w;
        }
        update(bel[l]);
      } else {
        for (int i = l; i <= ed[bel[l]]; i++) {
          A[i] += w;
        }
        for (int i = bel[l] + 1; i < bel[r]; i++) {
          mark[i] += w;
        }
        for (int i = st[bel[r]]; i <= r; i++) {
          A[i] += w;
        }
        update(bel[l]);
        update(bel[r]);
      }
    } else {
      int ans = 0;
      if (bel[l] == bel[r]) {
        for (int i = l; i <= r; i++) {
          if (A[i] + mark[bel[l]] >= w)
            ans++;
        }
      } else {
        for (int i = l; i <= ed[bel[l]]; i++) {
          if (A[i] + mark[bel[l]] >= w)
            ans++;
        }
        for (int i = bel[l] + 1; i < bel[r]; i++) {
          ans +=
              v[i].end() - lower_bound(v[i].begin(), v[i].end(), w - mark[i]);
        }
        for (int i = st[bel[r]]; i <= r; i++) {
          if (A[i] + mark[bel[r]] >= w)
            ans++;
        }
      }
      cout << ans << endl;
    }
  }
  return 0;
}