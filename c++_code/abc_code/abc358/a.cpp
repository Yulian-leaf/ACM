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
ll ExpGcd(ll a, ll b, ll &x, ll &y)
{
    ll q, temp;
    if (!b)
    {
        q = a;
        x = 1;
        y = 0;
    }
    else
    {
        q = ExpGcd(b, a % b, x, y);
        temp = x;
        x = y;
        y = temp - (a / b) * y;
    }
    return q;
}

ll Inv(ll a, ll n)
{
    ll x, y;
    ExpGcd(a, n, x, y);
    x = (x % n + n) % n;
    return x;
}
void solve()
{
    string a,b;
    cin>>a>>b;
    if(a=="AtCoder"&&b=="Land"){
        cout<<"Yes";
    }else cout<<"No";
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