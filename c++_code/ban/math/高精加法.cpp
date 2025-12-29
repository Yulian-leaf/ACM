#include <vector>
#include <iostream>
using namespace std;
vector<int> add(vector<int> a, vector<int> b) {
	vector<int> c;
	int t = 0;
	for (int i = 0; i < max(a.size(), b.size()); i++) {
		if (i < a.size())
			t += a[i];
		if (i < b.size())
			t += b[i];
		c.push_back(t % 10);
		t /= 10;
	}
	if (t)
		c.push_back(t);
	return c;
}

int main() {
	string a, b;
	vector<int> x, y, z;
	cin >> a >> b;
	for (int i = a.length() - 1 ; i >= 0 ; i--)
		x.push_back(a[i] - '0');
	for (int i = b.length() - 1 ; i >= 0 ; i--)
		y.push_back(b[i] - '0');

	z = add(x, y);
	for (int i = z.size() - 1 ; i >= 0 ; i--)
		cout << z[i];
	return 0;
}