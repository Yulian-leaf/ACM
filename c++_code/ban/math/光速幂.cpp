#include <bits/stdc++.h>
#define ll long long

inline ll Getphi(ll x)
{
	ll phi = x;
	for (ll i = 2; i * i <= x; i++)
		if (!(x % i))
		{
			phi = phi / i * (i - 1);
			while (!(x % i))
				x /= i;
		}
	if (x != 1)
		phi = phi / x * (x - 1);
	return phi;
}
ll lmx[100010][2], p, sq, a;

void init()
{
	sq = sqrt(p);
	lmx[0][0] = lmx[0][1] = 1;
	for (ll i = 1; i <= sq; i++)
		lmx[i][0] = lmx[i - 1][0] * a % p;
	for (ll i = 1; i <= sq; i++)
		lmx[i][1] = lmx[i - 1][1] * lmx[sq][0] % p;
}

inline ll ksm(ll a, ll b)
{
	b %= Getphi(p);
	return lmx[b % sq][0] * lmx[b / sq][1] % p;
}

inline void solve()
{
	ll b;
	scanf("%lld%lld%lld", &a, &b, &p);
	init();
	printf("%lld", ksm(a, b));
}