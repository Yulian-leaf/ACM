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
    int n, m;
    cin >> n >> m;
    vector<int> a(m + 10);
    for (int i = 1; i <= m; i++)
    {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++)
    {
        vector<int> b(m + 10);
        for (int j = 1; j <= m; j++)
        {
            cin >> b[j];
            a[j] -= b[j];
        }
    }
    for (int i = 1; i <= m; i++)
    {
        if (a[i] > 0)
        {
            cout << "No" << Endl;
            return;
        }
    }
    cout << "Yes" << Endl;
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