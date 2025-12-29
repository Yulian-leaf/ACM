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
int b[10000];
void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> a(n + 10);
    int cnt = 0, cep = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++)
    {
        if (a[i] > a[m])
            cnt++;
        if (a[i] == a[m])
            cep++;
    }
    cep--;
    // cout << cnt << " " << cep << Endl;
    if (cnt + cep < k)
    {
        cout << "YES" << Endl;
        return;
    }
    else
    {
        if (cnt >= k)
        {
            cout << "NO" << Endl;
        }
        else
        {
            cout << "MAYBE" << Endl;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
    {
        solve();
    }
    return 0;
}