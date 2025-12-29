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
const int N = 1e5 + 10, mod = 1e9 + 7;
int fact[N], ifact[N];

int qmi(int a, int b)
{
    int res = 1;
    while (b)
    {
        if (b & 1)
            res = (ll)res * a % mod;
        a = (ll)a * a % mod;
        b >>= 1;
    }
    return res;
}
ll C(int a,int b){
    return (ll)fact[a] * ifact[b] % mod * ifact[a - b] % mod;
}
void init(){
    fact[0] = ifact[0] = 1;
    for (int i = 1; i < N; i++)
    {
        fact[i] = (ll)fact[i - 1] * i % mod;
        ifact[i] = (ll)ifact[i - 1] * qmi(i, mod - 2) % mod;
    }    
}
void solve()
{
    init();
    int n;
    cin >> n;
    while (n--)
    {
        int a, b;
        cin >> a >> b;
        printf("%lld\n", C(a,b));
    }
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