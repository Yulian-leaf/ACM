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
char change(int x)
{
    return x - 'A' + 'a';
}
char rec(int x)
{
    return x - 'a' + 'A';
}
void solve()
{
    int n;
    cin>>n;
    for(int i=1;i<=pow(3,n);i++){
        for(int j=1;j<=pow(3,n);i++){
            if(i)
        }
    }
    if(n==1)return ;

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