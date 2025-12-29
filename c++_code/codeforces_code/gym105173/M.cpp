#pragma GCC optimize(3, "Ofast", "inline")
#include <bits/stdc++.h>
#define inf 0x3f3f3f3f3f
using namespace std;
using ll = long long;
const int N = 1e3 + 7;
const int mod = 998244353;
struct Point
{
    ll x, y;
    ll operator^(Point b) const
    {
        return x * b.y - y * b.x;
    }
    ll operator*(Point b) const
    {
        return x * b.x + y * b.y;
    }
} p[N];
int n;
Point operator-(Point x, const Point &y)
{
    x.x -= y.x, x.y -= y.y;
    return x;
}
ll dis(Point a, Point b)
{
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}
ll solve(Point A, Point B)
{
    Point V = (B - A);
    ll L = 0, R = 0;
    map<ll, int> mp1, mp2;
    for (int i = 1; i <= n; i++)
    {
        Point M = (p[i] - A);
        if ((V ^ M) == 0)
            continue;
        if ((V ^ M) < 0)
        {
            if (dis(p[i], A) == dis(p[i], B))
            {
                L++;
            }
        }
        else
        {
            Point Q = p[i] - B, P = p[i] - A;
            if (Q * V == 0)
            {
                mp2[dis(p[i], B)]++;
            }
            if (V * P == 0)
            {
                mp1[dis(p[i], A)]++;
            }
        }
    }
    // cout << L << '\n';
    for (auto [x, y] : mp1)
    {
        if (mp2[x])
        {
            R++;
        }
    }
    // cout << L << ' ' << R << '\n';
    return L * R;
}
int main()
{
    // int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> p[i].x >> p[i].y;
    }
    ll ans = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (i == j)
                continue;
            ans += solve(p[i], p[j]);
        }
    }
    cout << ans << '\n';
}
