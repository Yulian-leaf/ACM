#include <iostream>
#include <cstring>
using namespace std;
char p[1000005], t[1000005];
int len1, len2;
int next1[1000005], next2[1000005];

void do_next() {
	next1[0] = 0;
	int i = 1;
	int len = 0;

	while (i < len2) {
		if (t[i] == t[len])
			next1[i++] = ++len;
		else {
			if (len > 0)
				len = next1[len - 1];
			else
				next1[i++] = len;
		}
	}
}

void kmp() {
	int i = 0, j = 0;
	next2[0] = -1;

	for (int i = 1; i < len2; i++)
		next2[i] = next1[i - 1];

	while (i < len1) {
		if (j == len2 - 1 && p[i] == t[j]) {
			cout << i - j + 1 << endl;
			j = next2[j];
			if (j == -1)
				j++;
		}
		if (p[i] == t[j]) {
			j++;
			i++;
		} else {
			j = next2[j];
			if (j == -1) {
				i++;
				j++;
			}
		}
	}
}

int main() {
	cin >> p >> t;
	len1 = strlen(p);
	len2 = strlen(t);

	do_next();

	kmp();

	for (int i = 0; i < len2; i++)
		cout << next1[i] << " ";

	return 0;
}