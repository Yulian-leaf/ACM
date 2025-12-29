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
vector<vector<int>>v(15);
map<int,int>mp;
vector<int>vis(15);
    int n,m,ans=110;
void dfs(int x,int cnt,int cep){
    for(int j=1;j<=n;j++){
    if(vis[j]==0){
        int temp=cnt;
        for(int k=0;k<v[j].size();k++){
            mp[v[j][k]]++;
            if(mp[v[j][k]]==1){
                cnt++;
            }
        } 
        if(cnt==m){
            ans=min(ans,cep);
            cout<<ans<<" ";
            for(int i=1;i<=m;i++)cout<<mp[i]<<" ";
            cout<<Endl;
            return ;
        }
        vis[j]=1;
        dfs(j,cnt,cep+1);
        vis[j]=0;
        cnt=temp;
        for (int k = 0; k < v[j].size(); k++)
        {
            mp[v[j][k]]--;
        }
    }
    }
}
void solve()
{

    cin>>n>>m;

    for(int i=1;i<=n;i++){
        string s;
        cin>>s;
        s=" "+s;
        for(int j=1;j<=m;j++){
            if(s[j]=='o')v[i].push_back(j);
        }
    }
    for(int i=1;i<=n;i++){
        ll cnt=0;
        //cout<<"i: "<<i;
        for(int k=0;k<v[i].size();k++){
            mp[v[i][k]]++;
            if(mp[v[i][k]]==1)cnt++;
            //cout<<" j: "<<k<<" v: "<<v[i][k]<<Endl;
        }
        if(cnt==m){
            ans=1;
            break;
        }
        //cout<<cnt<<" ";
        dfs(i,cnt,2);
        mp.clear();
    }
    cout<<ans;
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