#include <iostream>
#include <vector>
using namespace std;

vector<int> mul(vector<int> &a, vector<int> &b) {
	vector<int> c(a.size() + b.size() + 7, 0);
	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j < b.size(); j++) {
			c[i + j] += a[i] * b[j];
		}
	}
	for (int i = 0; i <= c.size(); i++) {
		if (c[i] >= 10) {
			c[i + 1] += c[i] / 10;
			c[i] = c[i] % 10;
		}
	}
	while (c.size() > 0 && c.back() == 0) {
		c.pop_back();
	}
	return c;
}

int main() {
	string a, b;
	cin >> a >> b;
	vector<int> x, y, z;
	for (int i = a.size() - 1; i >= 0; i--)
		x.push_back(a[i] - '0');
	for (int i = b.size() - 1; i >= 0; i--)
		y.push_back(b[i] - '0');
	z = mul(x, y);
	for (int i = z.size() - 1; i >= 0; i--)
		cout << z[i];
	return 0;
}