#include <bits/stdc++.h>
#define Endl "\n"
#define int long long
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
void solve()
{
    int n,q;
    cin>>n>>q;
    vector<int>a(n+10),s(n+10);
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        cin>>s[i];
    }
    //0--lock  1--activate
    int num=sqrt(n);
    vector<int>st(num+10,0),ed(num+10,0),mark(num+10,0),sum(num+10,0),add(num+10,0),bel(n+10);
    //mark--activate_num  sum--sum  
    for(int i=0;i<=num;i++){
        st[i]=i*(n/num)+1;
        ed[i]=(i+1)*(n/num);
        if(i==num)ed[i]=n;
    }
    for(int i=0;i<=num;i++){
        sum[i]=0;
        mark[i]=0;
        add[i]=0;
        for(int j=st[i];j<=ed[i];j++){
            sum[i]+=a[j];
            mark[i]+=s[j];
            bel[j]=i;
        }
        // cout<<"st: "<<st[i]<<" ed: "<<ed[i]<<" sum: "<<sum[i]<<" mark: "<<mark[i]<<Endl;
    }
    // 0--lock  1--activate
    while(q--){
        int opt;
        cin>>opt;
        if(opt==1){
            //1-->0
            int x;
            cin>>x;
            s[x]=0;
            a[x]+=add[x/num];
            mark[x/num]--;
        }
        else if(opt==2){
            //0-->1
            int x;
            cin>>x;
            s[x]=1;
            a[x]-=add[x/num];
            mark[x/num]++;
        }
        else if(opt==3){
            int l,r,x;
            cin>>l>>r>>x;
            int front=bel[l],back=bel[r];
            if(front==back){
                for(int i=l;i<=r;i++){
                    if(s[i]==1)a[i]+=x,sum[front]+=x;
                }
            }else{
                for(int i=l;i<=ed[front];i++){
                    if(s[i]==1)a[i]+=x,sum[front]+=x;
                }
                for(int i=front+1;i<back;i++){
                    add[i]+=x;
                    sum[i]+=x*mark[i];
                }
                for(int i=st[back];i<=r;i++){
                    if(s[i]==1)a[i]+=x,sum[back]+=x;
                }                
            }

        }
        else if(opt==4){
            int l,r;
            ll ans=0;
            cin>>l>>r;
            int front=bel[l],back=bel[r];
            if(front==back){
                for(int i=l;i<=r;i++){
                    ans+=a[i];
                    if(s[i]==1)ans+=add[front];
                }
            }else{
                for(int i=l;i<=ed[front];i++){
                    ans+=a[i];
                    if(s[i]==1)ans+=add[front];
                }
                for(int i=front+1;i<back;i++){
                    ans+=sum[i];
                }
                for(int i=st[back];i<=r;i++){
                    ans+=a[i];
                    if(s[i]==1)ans+=add[back];
                }                
            }

            cout<<ans<<Endl;
        }
        // cout<<q<<" opt: "<<opt<<Endl;
        // for(int i=0;i<=num;i++){
        //     cout<<"st: "<<st[i]<<" ed: "<<ed[i]<<" sum: "<<sum[i]<<" mark: "<<mark[i]<<" add: "<<add[i]<<Endl;
        // }
        // for(int i=1;i<=n;i++){
        //     cout<<a[i]<<" ";
        // }
        // cout<<Endl;
    }

}

signed main()
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