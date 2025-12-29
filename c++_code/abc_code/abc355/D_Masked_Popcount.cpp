#include <bits/stdc++.h>
#define Endl "\n"
typedef long long ll;
typedef unsigned long long ull;
using namespace std;

inline void read(int &a)
{
    int s = 0, w = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            w = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        s = s * 10 + ch - '0';
        ch = getchar();
    }
    a = s * w;
}
const int M = 998244353;
void solve()
{
    ull n, m;
    cin >> n >> m;
    ull base = 2;
    vector<int> ss(66);
    vector<int> le(66);
    vector<int> ln(66);
    vector<int> sum(66);
    ss[0] = 1;
    for (int i = 1; i <= 60; i++)
    {
        ss[i] = ss[i - 1] * base;
    }
    ull ans = 0, an = 0;
    ull cap = m, cnt = 0, te = 0;
    while (cap > 0)
    {
        le[++cnt] = cap % 2;
        sum[cnt] = le[cnt] + sum[cnt - 1];
        if (cap % 2 == 1)
            te++;
        cap /= 2;
    }
    for (int i = 0; i <= 60; i++)
    {
        if (m < ss[i])
        {
            an = i;
            break;
        }
    }
    ull cep = n / ss[an];
    if (an > 0)
        ans = (cep * te * (an)) % M;
    // cout << (cep * te * (ss[an] - 1)) << Endl;
    ull ot = n % ss[an];
    ull temp = ot;

    for (int i = an; i >= 1; i--)
    {
        if (temp >= ss[i])
        {

            ans += (temp / ss[i] * sum[i] * i);
            temp %= ss[i];
            cout << temp << " " << sum[i] << Endl;
        }
    }
    // cnt = 0;
    //  while (temp > 0)
    //  {
    //      ln[++cnt] = temp % 2;
    //      temp /= 2;
    //  }
    //  for (int i = 1; i <= cnt; i++)
    //  {
    //      if (ln[i] == 1 && le[i] == 1)
    //      {
    //          ans++;
    //      }
    //  }
    cout << "cep: " << cep << " an: " << an << " te: " << te << " ans: " << ans << Endl;
    cout << ans % M << Endl;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
    {
        solve();
    }
    return 0;
}