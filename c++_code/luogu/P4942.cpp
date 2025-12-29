#include <iostream>
#include <cstdio>
using namespace std;
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        long long l, r;
        cin >> l >> r;
        long long cnt = (r - l + 1) % 9;
        ;
        long long ans = cnt * (l % 9) % 9 + (cnt) * (cnt - 1) % 9 * 5 % 9;
        cout << ans % 9 << endl;
    }
    return 0;
}