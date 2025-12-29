#include<bits/stdc++.h>
typedef long long ll;
#define Endl '\n';
using namespace std;
void solve(){
    ll n,p;
    cin>>n>>p;
    vector<ll>a(n+10),sum(n+10);
    for(int i=1;i<=n;i++){
        cin>>a[i];
        sum[i]=a[i]+sum[i-1];
    }
    ll k,t,ans=0;
    cin>>k>>t;
    if (t >= 2*p+ n)
    {
        ans=sum[n]+(t-(n-1)+t)*n*k/2;
    }
    else if (t >=min(p,n-p)+n)
    {
        ll temp=0;
        
        if(p<n-p){
            //op-->left
            temp= sum[n] + (t - (n - 1) + t) * n*k / 2;
            ans=max(ans,temp);
            //op==>right
            ll st=n;
            ll ed=p-(t-(n-p)*2+1);
            temp=sum[n]-sum[ed]+(st-ed)*(t-(n-p)+1+st-ed+t-(n-p)+1)*k/2;
            ans=max(ans,temp);
        }else{
            //op-->right
            temp = sum[n] + (t - (n - 1) + t) * n *k/ 2;
            ans = max(ans, temp);
            //op-->left
            ll st = 1;
            ll ed = t-p+1;
            temp = sum[ed] - sum[st] + (ed - st) * (ed - st +p+p)*k / 2;
            ans = max(ans, temp);
        }
    }else{
        ll temp;
        //once-->left
        if(t>p){
            temp=(t-p+t)*p/2+sum[p]+k*(t-p+t+2)*(p)/2;
        }else{
            temp=sum[p]-sum[p-t]+k*(1+t)*t/2;
        }
        ans=max(ans,temp);
        //once-->right
        if(t>(n-p)){
            temp=(t+t-(n-p+1))*(t-(n-p+1))*k/2+sum[n]-sum[p-1];
        }else{
            temp=sum[t+p-1]-sum[p-1]+(1+t)*t*k/2;
        }
        ans=max(ans,temp);
        //change-channel-->left
        for(int k=1;k<=p;k++)
            temp=max(temp,sum[p+t-(k)*2-1]-sum[p-k-1]+(k+1+t)*(t-k-1)*k/2);
        ans=max(ans,temp);
        //change-channel-->right
        for(int k=1;k<=n-p;k++)
            temp = max(temp, sum[p+k] - sum[p - (t - 2*k-1)] + (k + 1 + t) * (t - k-1)*k / 2);
        ans=max(ans,temp);
    }        
    cout<<ans<<Endl;
    return ;
}

int main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}