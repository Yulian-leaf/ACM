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
vector<ll>ss(60);
void init(){
    ss[0] = 1;
    for (int i = 1; i <= 30; i++)
    {
        ss[i] = ss[i - 1] * 2;
    }
}
void solve()
{
    ll a,b;
    cin>>a>>b;
    vector<ll>aa(60),bb(60);
    int cnt=0;
    while(a>0){
        aa[++cnt]=a%2;
        a/=2;
    }
    int cep=cnt;
    cnt=0;
    while(b>0){
        bb[++cnt]=b%2;
        b/=2;
    }
    int ans=0;
    int temp=0;
    cnt=max(cnt,cep);
    for(int i=1;i<=cnt;i++){
        //cout<<aa[i]<<" "<<bb[i]<<Endl;
        if(aa[i]==bb[i]){
            temp++;
        }else break;
    }
    cout<<ss[temp]<<Endl;
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
        //cout<<"case"<<T<<": "<<Endl;
        solve();
    }
    return 0;
}