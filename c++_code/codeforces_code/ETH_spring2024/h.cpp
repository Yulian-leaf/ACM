
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
    map<int,vector<int> >mp;
    int n,m;
    cin>>n>>m;
    vector<int>a(n+10),b(n+10);
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n;i++)cin>>b[i];
    for(int i=1;i<=n;i++){
        mp[a[i]].push_back(b[i]);
    }
    for(int i=1;i<=m;i++){
        sort(mp[i].begin(),mp[i].end());
    }
    ll j=0;
    for(ll cnt=0;cnt<=100000;cnt++){
        priority_queue<int> pq;
        for (int i = 1; i <= m; i++)
        {
            
            if (mp[i].empty())
            {
                cout << cnt << Endl;
                return;
            }
            pq.push(mp[i][0]);
        }
        while(!pq.empty()){
            ll s=pq.top();
            pq.pop();
            if(j<=s){
                cout<<cnt<<Endl;
                return ;
            }
            j++;
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