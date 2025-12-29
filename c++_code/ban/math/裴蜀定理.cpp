//≈· Ò∂®¿Ì
#include <iostream>
using namespace std;

int gcd(int a, int b) {
	if (!b)
		return a;
	else
		return gcd(b, a % b);
}

int main() {
	int n;
	cin >> n;
	int x, ans = 0;
	cin >> ans;
	ans = abs(ans);
	n--;
	while (n--) {
		cin >> x;
		x = abs(x);
		ans = gcd(max(ans, x), min(ans, x));
	}
	cout << ans;
	return 0;
}