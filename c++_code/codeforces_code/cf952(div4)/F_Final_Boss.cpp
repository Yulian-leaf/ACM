
#include <bits/stdc++.h>
#define Endl "\n"
typedef unsigned long long ull;
using namespace std;
inline void read(__int128 &X)
{
    X = 0;
    int w = 0;
    char ch = 0;
    while (!isdigit(ch))
    {
        w |= ch == '-';
        ch = getchar();
    }
    while (isdigit(ch))
        X = (X << 3) + (X << 1) + (ch ^ 48), ch = getchar();
    if (w)
        X = -X;
}

void print(__int128 x)
{
    if (!x)
        return;
    if (x < 0)
        putchar('-'), x = -x;
    print(x / 10);
    putchar(x % 10 + '0');
}
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
    int h,n;
vector<__int128_t>a(200005),c(200005);
bool check(__int128_t x){
    __int128_t sum=0;
    for(int i=1;i<=n;i++){
        sum+=(x/c[i])*a[i];
    }
    //cout<<x<<" "<<sum<<Endl;
    if(sum>=h)return 1;
    return 0;

}
void solve()
{

    cin>>h>>n;
    __int128_t sum=0;
    for(int i=1;i<=n;i++){
        read(a[i]);
        sum+=a[i];
    }
    for(int i=1;i<=n;i++)read(c[i]);
    h-=sum;
    if(h<0){
        cout<<1<<Endl;
        return ;
    }
    __int128_t l=0,r=1e17,ans=1;
    while(l<=r){
        __int128_t mid=(l+r)/2;
        if(check(mid)){
            //cout<<mid<<" ";
            r=mid-1;
            ans=mid;
        }
        else{
            
            l=mid+1;
        }
    }
    print(ans+1);
    cout<<Endl;
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