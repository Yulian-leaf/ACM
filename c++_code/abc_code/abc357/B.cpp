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
char change(int x){
    return x-'A'+'a';
}
char rec(int x){
    return x-'a'+'A';
}
void solve()
{
    string s;
    cin>>s;
    int n=s.length();
    s=" "+s;
    int sum1=0,sum2=0;
    for(int i=1;i<=n;i++){
        if(s[i]>='a'&&s[i]<='z')sum1++;
        if(s[i]>='A'&&s[i]<='Z')sum2++;
    }
    if(sum2>sum1){
        for(int i=1;i<=n;i++){
            if(s[i]>='A'&&s[i]<='Z')cout<<s[i];
            else cout<<rec(s[i]);
        }

    }else{
        for (int i = 1; i <= n; i++)
        {
            if (s[i] >= 'a' && s[i] <= 'z')
                cout << s[i];
            else
                cout << change(s[i]);
        }
    }
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