#include<iostream>
typedef long long ll;
using namespace std;
void solve(){
    ll l,r;
    cin>>l>>r;
    int temp,cnt=0,ans=0,rr=r,ll=l;
    while(l>0){
        cnt++;
        if(cnt==1)temp=r%10;
        if(l%10!=r%10){
            ans=cnt*2;
            if(r%10>=5&&l%10<5){
                ans--;
            }
        }
        l/=10;
        r/=10;
    }
    if(r>0){
        if(temp>=5){
            cout<<5;
        }else cout<<1;
        while(rr>0){
            rr/=10;
            cout<<0;
            
        }
    }
}
int main(){
    int T=1;
    cin>>T;
    while(T--){
        solve();
    }
}