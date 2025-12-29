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
    int n;
    cin >> n;
    vector<ll> a(n + 10), b(n + 10);
    vector<ll> v(n + 10);
    int cnt = 0;
    map<ll, ll> mp;
    map<ll, ll> sb;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> b[i];
        sb[b[i]]++;
        if (b[i] == a[i])
            continue;
        if (mp[b[i]] == 0)
            mp[b[i]] = ++cnt;
        v[cnt]++;
    }
    ll m, te;
    cin >> m;
    while (m--)
    {
        ll x;
        cin >> x;
        if (mp[x] != 0)
        {
            v[mp[x]]--;
            if (v[mp[x]] == 0)
            {
                mp[x] = 0;
                cnt--;
            }
        }
        if (m == 0)
            te = x;
    }
    if (cnt <= 0 && sb[te] != 0)
        cout << "YES" << Endl;
    else
        cout << "NO" << Endl;
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