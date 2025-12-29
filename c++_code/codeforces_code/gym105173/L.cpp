#include <bits/stdc++.h>
#define Endl "\n"
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
const int mod = 998244353;
void solve()
{
    string s;
    cin >> s;
    vector<int> v;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == ')')
        {
            if (s[i - 1] == '(')
            {
                v.push_back(1);
            }
            else
            {
                v.push_back(2);
            }
        }
    }
    reverse(v.begin(), v.end());
    ll ans = 1;
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i] == 2)
        {
            ans *= i + 1;
            ans %= mod;
        }
    }
    cout << ans << Endl;
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