
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
    int n,m;
    cin>>n>>m;
    int maxx=0,ans=0;
    vector<vector<char> >s (n+10 , vector<char>(m+10));
    for(int i=1;i<=n;i++){
        string ss;
        cin>>ss;
        ss=" "+ss;
        int cnt=0;
        for(int j=1;j<=m;j++){
            s[i][j]=ss[j];
            if(ss[j]=='#')cnt++;
        }
        if(cnt>maxx){
            maxx=cnt;
            ans=i;
        }
    }
    int cne=0;
    for(int j=1;j<=m;j++){
        if(s[ans][j]=='#')cne++;
        if(cne==maxx/2+1){
            cout<<ans<<" "<<j<<Endl;
            return ;
        }
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