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
vector<ll> yul(99);
void init()
{
    ll base = 2;

    yul[0] = 1;
    for (int i = 1; i <= 55; i++)
    {
        yul[i] = yul[i - 1] * base;
    }
}
void solve()
{
    ll l, r;
    cin >> l >> r;
    int ans = 0;
    for (int i = 1; i <= 40; i++)
    {
        if (yul[i] >= l && yul[i] <= r)
            ans = i;
    }
    cout << ans << Endl;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    cin >> T;
    init();
    while (T--)
    {
        solve();
    }
    return 0;
}