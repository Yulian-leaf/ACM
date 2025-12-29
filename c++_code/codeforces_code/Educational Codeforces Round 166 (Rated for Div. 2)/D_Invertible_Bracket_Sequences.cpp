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
    string s;
    cin >> s;
    int n = s.length();
    s = " " + s;
    int ans = (n - 1) * n / 2;
    int j = 0;
    for (int i = 2; i <= n; i++)
    {
        if (s[i] == s[i - 1])
        {
            j++;
        }
        else
        {
            ans -= j * (j + 1) / 2;
            j = 0;
        }
    }
    cout << ans << Endl;
    return;
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