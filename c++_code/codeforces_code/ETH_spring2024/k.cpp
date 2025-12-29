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
long long quick_mul(long long x, long long y, long long mod)
{
    long long ans = 0;
    while (y != 0)
    {
        if (y & 1 == 1)
            ans += x, ans %= mod;
        x = x + x, x %= mod;
        y >>= 1;
    }
    return ans;
}

ll qp(int base, int power, int mod)
{
    ll result = 1;
    while (power > 0)
    {
        if (power & 1)
        {

            result=quick_mul(result,base,mod);
            result %= mod;
        }

        power >>= 1;
        base=quick_mul(base,base,mod);
        base %= mod;
    }
    return result;
}
const ll p=1e9+7;
void solve()
{
    ll n,k;
    cin>>n>>k;
    ll a,b;
    cin>>a>>b;
    ll up=(qp(b-a,k,p)*qp(b,n,p))%p;
    ll down=(((qp(b,n,p)-qp(b-a,n,p))%p)*qp(b,k,p)*a)%p;
    //cout<<up<<" "<<down<<Endl;
    // ll d=__gcd(up,down);
    // up/=d;
    // down/=d;
    //
    cout<<(quick_mul(up,Inv(down,p),p))%p<<Endl;
    //cout<<up<<" "<<down<<Endl;

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