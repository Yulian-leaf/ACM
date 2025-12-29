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
ll nn,p,cep;
ll Inv(ll a, ll n)
{
    ll x, y;
    ExpGcd(a, n, x, y);
    x = (x % n + n) % n;
    return x;
}
queue<int>q;
void dfs(ll x){
    if(x/(cep/10)>=1){
        q.push(x);
        return ;
    }
    dfs(x*10+1);
    dfs(x*10+2);
}
const ll N=99;
ll lca(ll x){
    vector<ll>f(N),a(N);
    ll n=0,ans=0;
    while(x>0)
    {
        n++;
        a[n]=x%10;
        x/=10;
        f[n] = 1;
    }
    for(int i=1;i<=n/2;i++)swap(a[i],a[n-i+1]);
   
    for (int i = 1; i <= n; i++){
    //cout<<a[i]<<" ";
        for (int j = 1; j < i; j++)
            if (a[j] <= a[i])
                f[i] = max(f[i], f[j] + 1);
                }
    for (int i = 1; i <= n; i++)
        ans = max(ans, f[i]);
    return ans;
}
void solve()
{
    
    cin>>nn>>p;
    cep=pow(10,nn);
    dfs(1);
    dfs(2);
    ll sum=0,cnt=0;
    // if(nn==2)
    // cout<<(7*Inv(4,p))%p;
    // else if(nn==3)
    // cout<<(10*(Inv(4,p)))%p;
    // else if(nn==4)
    // cout<<(25*Inv(8,p))%p;
    // else{
     
    // }
    //cout<<Endl;
    while(!q.empty()){
        int x=q.front();
        //cout<<" x: "<<x<<" ";
        cnt++;
        sum+=lca(x);
        //cout<<" sum: "<<sum<<Endl;
        q.pop();
    }
    ll d=__gcd(cnt,sum);
    cnt/=d;
    sum/=d;
    cout<<(sum*Inv(cnt,p))%p;
    //cout<<cnt<<" "<<sum;
    
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