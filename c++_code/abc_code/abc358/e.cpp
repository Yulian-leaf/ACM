#include <bits/stdc++.h>
const int mod = 998244353;
#define ll long long
#define N 1010
using namespace std;
ll n, a[N], C[N][N], dp[30][N];
int main()
{
    ll i, j, k;
    for (i = 0; i < N; i++)
    {
        C[i][0] = 1;
        for (j = 1; j <= i; j++)
        {
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
        }
    }
    cin >> n;
    for (i = 0; i < 26; i++)
    {
        cin >> a[i];
    }
    dp[0][0] = 1;
    for (i = 0; i < 26; i++)
    {
        for (j = 0; j <= n; j++)
        {

            for (k = 0; k <= a[i] && j + k <= n; k++)
            {
                dp[i + 1][j + k] = (dp[i + 1][j + k] + dp[i][j] * C[j + k][k]) % mod;
            }
        }
    }
    ll ans = 0;
    for (i = 1; i <= n; i++)
    {
        ans = (ans + dp[26][i]) % mod;
    }
    cout << ans << '\n';
    return 0;
}