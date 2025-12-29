#include <bits/stdc++.h>
#define Endl "\n"
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
double judge(ll x){
    if (x >= 10000000){
        return 2;
    }else if(x>=9800000){
        return 1+(double(x-9800000))/200000;
    }else{
        return (double(x-9500000))/300000;
    }
}
void solve()
{
    ll n;
    double cep;
    cin>>n>>cep;
    // cout<<n<<" "<<cep<<Endl;
    printf("%.7f\n",max(0.0,judge(n)+cep));
}

int main()
{
    // ios::sync_with_stdio(false);
    // cin.tie(0);
    // cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
    {
        solve();
    }
    return 0;
}