#include <bits/stdc++.h>
#define Endl "\n"
#define int long long
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
#define Ios ios::sync_with_stdio(false), cin.tie(0)
#define int long long

const int N = 5e5+10,mod=10000339;
int T, n, m;
char a[N];
unsigned long long hl[N], hr[N], p[N], P = 131;

int queryl(int l, int r)
{
    return (hl[r] - (hl[l - 1] * p[r - l + 1])%mod+mod)%mod;
}
int queryr(int l, int r)
{
    return (hr[l] - (hr[r + 1] * p[r - l + 1])%mod+mod)%mod;
}
void solve(){
    cin >> a + 1;
    n = strlen(a + 1);

    p[0] = 1;
    for (int i = 1; i <= n; i++)
        p[i] = (p[i - 1] * P)%mod, hl[i] = ((hl[i - 1] * P)%mod + a[i])%mod;
    for (int i = n; i >= 1; i--)
        hr[i] = ((hr[i + 1] * P)%mod + a[i])%mod;

    int l = 1;
    while (l < n && a[l] == a[n])
        l++, n--;

    if (l >= n)
    {
        cout << "Yes"<<Endl;
        return ;
    }

    for (int i = l; i < n; i++)
    {
        if (a[i] != a[n])
            continue;
        if (((queryr(l, i) * p[n - i])%mod + queryl(i + 1, n))%mod == ((queryr(i + 1, n) * p[i - l + 1])%mod + queryl(l, i))%mod)
        {
            cout<<"Yes"<<Endl;
            return ;
        }
    }
    for (int i = l + 1; i <= n; i++)
    {
        if (a[i] != a[l])
            continue;
        if ((queryl(l, i - 1) * p[n - i + 1]%mod + queryr(i, n))%mod ==( queryl(i, n) * p[i - l]%mod + queryr(l, i - 1))%mod)
        {
            cout <<"Yes"<<Endl;
            return ;
        }
    }
    cout << "No"<<Endl;
}
signed main()
{
    Ios;
    int T=1;
    cin>>T;
    while(T--){
        solve();        
    }

    return 0;
}
