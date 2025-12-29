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
    int n;
    cin >> n;
    string s;
    cin >> s;
    int temp = 0;
    int fla = 1, cep = 0;
    char te = 'a';
    for (int i = 0; i < n; i++)
    {
        if (s[i] >= 'a' && s[i] <= 'z')
        {
            cep = 1;
            if (s[i] >= te)
            {
                te = s[i];
            }
            else
            {
                fla = 0;
            }
        }
        else
        {
            if (cep == 1)
                fla = 0;
            if (s[i] >= temp)
            {
                temp = s[i];
            }
            else
            {
                fla = 0;
            }
        }
    }
    if (fla == 1)
        cout << "YES" << Endl;
    else
        cout << "NO" << Endl;
    return;
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