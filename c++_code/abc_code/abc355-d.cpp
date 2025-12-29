#include <bits/stdc++.h>
#define Endl "\n"
typedef long long ll;
typedef unsigned long long ull;
using namespace std;

inline void read(int &a) {
	int s = 0, w = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-')
			w = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		s = s * 10 + ch - '0';
		ch = getchar();
	}
	a = s * w;
}

void solve() {
	int n;
	cin>>n;
	vector<int>l(n),r(n);
	for(int i=0;i<=n-1;i++){
        cin>>l[i]>>r[i];
	}
    sort(l.begin(),l.end());
    sort(r.begin(),r.end());
    int ans=n*(n-1)/2;
    for(int i=0,j=0;i<n;i++){
        while(j<n&&r[j]<l[i]){
            j++;
        }
        ans-=j;
    }
    cout<<ans<<Endl;
	return ;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int T = 1;
	//cin >> T;
	while (T--) {
		solve();
	}
	return 0;
}