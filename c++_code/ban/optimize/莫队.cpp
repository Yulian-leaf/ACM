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
const int N = 50005;
ll n, m, maxn;
ll c[N];
ll sum;
ll cnt[N];
ll ans1[N], ans2[N];

struct query
{
    int l, r, id;

    bool operator<(const query &x) const
    {
        if (l / maxn != x.l / maxn)
            return l < x.l;
        return (l / maxn) & 1 ? r < x.r : r > x.r;
    }
} a[N];

void add(int i)
{
    sum += cnt[i];
    cnt[i]++;
}

void del(int i)
{
    cnt[i]--;
    sum -= cnt[i];
}
ll gcd(ll x, ll y)
{
    if (!y)
        return x;
    else
        return gcd(y, x % y);
}
void solve()
{
    cin >> n >> m;
    maxn = sqrt(n);
    for (int i = 1; i <= n; i++)
        cin >> c[i];
    for (int i = 0; i < m; i++)
        cin >> a[i].l >> a[i].r, a[i].id = i;
    sort(a, a + m);
    for (int i = 0, l = 1, r = 0; i < m; i++)
    {
        if (a[i].l == a[i].r)
        {
            ans1[a[i].id] = 0, ans2[a[i].id] = 1;
            continue;
        }
        while (l > a[i].l)
            add(c[--l]);
        while (r < a[i].r)
            add(c[++r]);
        while (l < a[i].l)
            del(c[l++]);
        while (r > a[i].r)
            del(c[r--]);
        ans1[a[i].id] = sum;
        ans2[a[i].id] = (ll)(r - l + 1) * (r - l) / 2;
    }
    for (int i = 0; i < m; i++)
    {
        if (ans1[i] != 0)
        {
            long long g = gcd(ans1[i], ans2[i]);
            ans1[i] /= g, ans2[i] /= g;
        }
        else
            ans2[i] = 1;
        cout << ans1[i] << "/" << ans2[i] << Endl;
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