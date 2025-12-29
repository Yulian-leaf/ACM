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
char b[111];
int an[111];
int n, m, k, ans;

vector<int> c(111);
vector<vector<int>> a(111, vector<int>(111));
bool check()
{
    for (int i = 1; i <= m; i++)
    {
        int cnt = 0;
        for (int j = 1; j <= c[i]; j++)
        {
            if (an[a[i][j]] == 1)
                cnt++;
        }
        if (b[i] == 'x')
        {
            if (cnt >= k)
                return 0;
        }
        if (b[i] == 'o')
        {
            if (cnt < k)
                return 0;
        }
    }
    return 1;
}
void dfs(int pos, int real)
{
    if (pos == n + 1)
    {
        if (check())
            ans++;
        return;
    }
    dfs(pos + 1, 0);
    an[pos] = 1;
    dfs(pos + 1, 1);
    an[pos] = 0;
}

void solve()
{
    cin >> n >> m >> k;
    for (int i = 1; i <= m; i++)
    {
        cin >> c[i];
        for (int j = 1; j <= c[i]; j++)
        {
            cin >> a[i][j];
        }
        cin >> b[i];
    }
    dfs(1, 0);
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