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
    int n,k;
    cin>>n>>k;
    string s;
    cin>>s;
    s=" "+s;
    int j=1;
    int temp=0,cep=0;
    for(int i=2;i<=n;i++){
        if(s[i]==s[i-1]){
            j++;
        }else{
            if(j==k){
                j=1;
                continue;
            }else{
                if(temp==0){
                    if(s[i]!=s[i-1])
                    temp=i,cep=j,j=1;   
                    else{
                        temp=i-k;
                        cep=j-k;
                        j=1;
                    }                 
                }else{
                    cout<<-1<<Endl;
                    return ;
                }
            }
        }
    }
    if(temp==0&&j==k){
        cout<<n<<Endl;
    }
    else{
        if(cep+j==k){
            cout<<temp<<Endl;
        }else{
            cout<<-1<<Endl;
        }
    }
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