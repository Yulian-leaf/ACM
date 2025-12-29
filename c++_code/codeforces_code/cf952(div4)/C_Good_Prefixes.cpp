
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
    ll sum=0,maxx=0,ans=0;
    for(int i=1;i<=n;i++){
        sum+=a[i];
        maxx=max(maxx,a[i]);
        if(maxx*2==sum)ans++;
    }
    cout<<ans<<Endl;
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