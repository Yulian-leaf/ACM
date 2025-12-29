#include <bits/stdc++.h>
using namespace std;

int main() {
	int a, b[12], cnt = 0;
	cin >> a;
	if (a > 0) {
		for (int i = 1; i < 12; i++) {
			b[i] = a % 10;
			cnt++;
			if (a / 10 < 10) {
				a /= 10;
				b[i + 1] = a % 10;
				cnt++;
				break;
			} else {
				a /= 10;
			}
		}
		for (int i = 1; i <= cnt - 1; i++) {
			if (b[i] == 0 ) {

			} else
				cout << b[i];
		}
		cout << b[cnt];
	} else if (a == 0) {
		cout << "0" << endl;
	} else {
		a = abs(a);
		for (int i = 1; i < 12; i++) {

			b[i] = a % 10;
			cnt++;
			if (a / 10 < 10) {
				a /= 10;
				b[i + 1] = a % 10;
				cnt++;
				break;
			} else {
				a /= 10;
			}
		}
		cout << "-";
		for (int i = 1; i <= cnt - 1; i++) {
			if (b[i] == 0 ) {

			} else
				cout << b[i];
		}
		cout << b[cnt];
	}

	return 0;
}