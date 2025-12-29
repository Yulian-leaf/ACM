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

void solve()
{
    ll n;
    cin >> n;
    vector<ll> a(n + 10), b(n + 10);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    for (int i = 1; i <= n + 1; i++)
    {
        cin >> b[i];
    }
    ll ans = 0, minn = 1e10;
    ll temp = b[n + 1];
    for (int i = 1; i <= n; i++)
    {
        ans += abs(a[i] - b[i]);
        if (a[i] <= temp && b[i] >= temp)
        {
            minn = 0;
        }
        else if (a[i] >= temp && b[i] <= temp)
        {
            minn = 0;
        }
        else
        {
            minn = min(min(abs(a[i] - temp), abs(b[i] - temp)), minn);
        }
        // cout << ans << " ";
    }
    cout << ans + 1 + minn << Endl;
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