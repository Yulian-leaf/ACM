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
    ll h, w, c;
    cin >> h >> w >> c;
    vector<vector<ll>> ac(h + 10, vector<ll>(w + 10));
    for (int i = 1; i <= h; i++)
    {
        for (int j = 1; j <= w; j++)
        {
            cin >> ac[i][j];
        }
    }
    vector<vector<ll>> dp(h + 10, vector<ll>(w + 10));
    for (int i = 0; i <= h; i++)
    {
        dp[i][0] = 1e17;
    }
    for (int i = 0; i <= w; i++)
    {
        dp[0][i] = 1e17;
    }
    ll ans = 1e17;

    for (int i = 1; i <= h; i++)
    {
        for (int j = 1; j <= w; j++)
        {
            dp[i][j]=1e17;
            if(i>1)
            dp[i][j]=min(dp[i][j],(dp[i - 1][j] - ac[i - 1][j] + ac[i][j] + c));
            if(j>1)
            dp[i][j] = min(dp[i][j], (dp[i][j - 1] - ac[i][j - 1] + ac[i][j] + c));
            if (i > 1)
                dp[i][j] = min(dp[i][j], ac[i - 1][j] + ac[i][j] + c);
            if (j > 1)
                dp[i][j] = min(dp[i][j], ac[i][j - 1] + ac[i][j] + c);
            ans = min(dp[i][j], ans);
            // cout<<dp[i][j]<<" ";
        }
        // cout<<Endl;
    }
    cout << ans;
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