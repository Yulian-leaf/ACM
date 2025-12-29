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
    cin>>n;
    vector<ll>a(n+10);
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    ll sum=a[1];
    for(int i=2;i<=n;i++){
        ll l=__gcd(a[i],sum);
        sum=a[i]*sum/l;
    }
    ll ans=0;
    vector<ll>b(n+10);
    for(int i=1;i<=n;i++){
        b[i]=sum/a[i];
        ans+=b[i];
    }
    if(ans>=sum){
        cout<<-1<<Endl;
    }else{
        for(int i=1;i<=n;i++)cout<<b[i]<<" ";
        cout<<Endl;
    }
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