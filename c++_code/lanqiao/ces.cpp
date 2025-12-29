
#include <bits/stdc++.h>
#define inf 0x3f3f3f3f3f3f3f3f
#define Endl '/n';
using namespace std;
typedef long long ll;
ll d[60];
long long n, S;
long long ans = 1e18;
bool dfs(ll now, ll p, ll res)
{
    if (p == -1)
    {
        if (now == 0)
        {
            ans = res;
            return true;
        }
        return false;
    }
    ll k = d[p] * (1ll << p);

    if (k <= now && (now - k) / n <= ll((1ll << p) - 1))
    {
        if (dfs(now - k, p - 1, res))
        {
            return true;
        }
    }
    k = (1ll << p) * (n - d[p]);
    if (k <= now && (now - k) / n <= ll((1ll << p) - 1))
    {
        return dfs(now - k, p - 1, res + (1ll << p));
    }
    return false;
}
void solve()
{

    cin >> n >> S;
    for (int i = 0; i < n; i++)
    {
        long long x;
        cin >> x;
        for (int j = 0; j < 60; j++)
        {
            if ((x >> j) % 2 == 1)
            {
                d[j]++;
            }
        }
    }

    dfs(S, 59, 0);
    if (ans == 1e18)
    {
        cout << -1 << Endl;
    }
    else
    {
        cout << ans << Endl;
    }
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