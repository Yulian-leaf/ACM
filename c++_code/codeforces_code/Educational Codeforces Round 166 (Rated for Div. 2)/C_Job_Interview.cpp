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
struct point
{
    int a, b, fl;
} s[200010];
bool cmp(point a, point b)
{
    return a.b < b.b;
}
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<ull> an(n + m + 10);
    for (int i = 1; i <= n + m + 1; i++)
    {
        cin >> s[i].a;
        s[i].fl = 0;
    }
    for (int i = 1; i <= n + m + 1; i++)
    {
        cin >> s[i].b;
    }
    ull ans = 0;
    ull cep = m, te = 0, cap = n, sub = 0;
    for (int i = 1; i <= n + m + 1; i++)
    {
        if ((s[i].b > s[i].a && cep >= 1))
        {
            ans += s[i].b;
            s[i].fl = 1;
            cep--;
        }
        else
        {
            if (cap == 0 && cep >= 1)
            {
                ans += s[i].b;
                s[i].fl = 1;
                sub = i;
                cep--;
                continue;
            }
            cap--;
            s[i].fl = 0;
            if (s[i].b > s[i].a && te == 0)
            {
                te = i;
                if (sub != 0 && s[sub].b < s[sub].a)
                {
                    ans -= s[sub].b;
                    ans += s[sub].a;
                    ans += s[i].b;
                    s[i].fl = 1;
                    s[sub].fl = 0;
                    te = 0;
                    continue;
                }
            }
            ans += s[i].a;
        }
    }
    if (te == 0)
        te = n + m + 1;
    if (s[te].fl == 1)
    {
        int temp = te;
        while (s[temp].fl == 1 && temp <= n + m + 1)
            temp++;
        if (temp == n + m + 2)
        {
            temp = te;
            while (s[temp].fl == 1)
                temp--;
        }
        te = temp;
    }

    for (int i = 1; i <= n + m + 1; i++)
    {
        if (s[i].fl == 1)
        { // promgram
            an[i] = ans - s[i].b + (s[te].b - s[te].a);
        }
        else
        {
            an[i] = ans - s[i].a;
        }
    }
    for (int i = 1; i <= n + m + 1; i++)
    {
        cout << an[i] << " ";
    }
    cout << Endl;
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