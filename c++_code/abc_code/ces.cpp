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

void solve()
{
	string s,t;
	cin>>s>>t;
	int n=s.size(),m=t.size();

	s=" "+s;
	t=" "+t;
	
	int w=0;
	for(int i=1;i<n;i++){
		if(s[i]==t[1]){
			for(int k=1;k<=n-i;k++){
				//cout<<i<<" "<<k<<Endl;
				if((k)*(m)+i<n)continue;
				if(k*(m-2)+i>n)break;
				ll fla=1;
				for(int w=1;w<=(m-1);w++){
					if(s[i+w*k]==t[w+1]){
					}
					else{
						fla=0;
						break;
					}
				}
				if(fla==0)continue;
				else {
					cout<<"Yes"<<Endl;
					return ;
				}
			}
		}
	}
	cout<<"No"<<Endl;
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