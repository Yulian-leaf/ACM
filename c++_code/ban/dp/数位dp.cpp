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
ll dp[20][20];
ll num[20];
// pos--当前位置  limit--上一位是否是最大  lead--前导0  dig--当前数位  sum--当前该数个数
ll dfs(int pos, int limit, bool lead, int dig, ll sum)
{
    ll ans = 0;
    if (pos == 0)
        return sum;
    if (!limit && lead && (dp[pos][sum] != -1))
        return dp[pos][sum];
    int up = 9;
    if (limit)
        up = num[pos];
    for (int j = 0; j <= up; j++)
    {
        ans += dfs(pos - 1, (j == up) && limit, lead || j, dig, sum + ((j || lead) && (j == dig)));
    }
    if (!limit && lead)
        dp[pos][sum] = ans;
    return ans;
}
ll dep(ll x, int d)
{
    memset(dp, -1, sizeof(dp));
    ll len = 0;
    while (x)
    {
        num[++len] = x % 10;
        x /= 10;
    }
    return dfs(len, 1, 0, d, 0);
}
void solve()
{
    ll l, r;
    cin >> l >> r;
    for (int i = 0; i <= 9; i++)
    {
        cout << dep(r, i) - dep(l - 1, i) << " ";
    }

    return;
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