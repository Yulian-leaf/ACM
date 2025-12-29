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
int mid(int a,int b,int c){
    if(a>=b){
        if(b>=c)return b;
        else{
            if(a>=c)return c;
            else return a;
        }
    }
    else {
        if(c<=a){
            return a;
        }else{
            if(c<=b)return c;
            else return b;
        }
    }
}
void solve()
{
    int n; 
    cin>>n;
    vector<int>a(n+10);
    int maxx=0;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        if(i>1){
            maxx=max(maxx,min(a[i],a[i-1]));
        }
    }
    for(int i=3;i<=n;i++){ 
        maxx=max(maxx,mid(a[i-2],a[i-1],a[i]));
    }
    cout<<maxx<<Endl;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int T = 1;
    cin >> T;
	while (T--)
	{
		solve();
	}
	return 0;
}