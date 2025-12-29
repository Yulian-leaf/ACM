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
vector<ll> te(33);
void pre()
{

    te[0] = 1;
    for (int i = 1; i <= 32; i++)
    {
        te[i] = te[i - 1] * 2;
    }
}
const int N = 99;
void solve()
{
    int x;
    cin >> x;
    vector<int> v;
    v.push_back(0);
    int temp = 0;
    while (x >= 2)
    {
        temp++;
        v.push_back(x % 2);
        x /= 2;
    }
    temp++;
    v.push_back(x);
    v.push_back(0);
    v.push_back(0);
    for (int i = 1; i <= temp; i++)
    {
        if (v[i] == 2)
        {
            v[i + 1]++;
            v[i] = 0;
        }
        if (v[i] == 1 && v[i + 1] == 1)
        {
            v[i + 2]++;
            v[i] = -1;
            if (v[i - 1] != 0)
            {
                if (v[i - 1] == 1)
                {
                    v[i] = 0;
                    v[i - 1] = -1;
                }
            }
            v[i + 1] = 0;
        }
    }
    while (v[temp + 1] != 0)
        temp++;
    cout << temp << Endl;
    for (int i = 1; i <= temp; i++)
        cout << v[i] << " ";

    cout << Endl;
    return;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    cin >> T;
    pre();
    while (T--)
    {
        solve();
    }
    return 0;
}