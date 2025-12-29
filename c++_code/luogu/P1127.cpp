#include<bits/stdc++.h>
#define Endl '\n'
typedef long long ll;
using namespace std;
map<string,int>mp;
ll ans=0,sum=0;
string aas;
int n;
string a[1001];
vector<int> e[1001];
int ind[1001];
int rnd[1001];
bool used[1001];
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
void dfs(int s, std::string curr, int count)
{
    if (count == n)
    {
        curr[curr.length() - 1] = ' ';
        std::cout << curr;
        exit(0);
    }
    for (auto i : e[s])
        if (!used[i])
        {
            used[i] = true;
            dfs(i, curr + a[i] + '.', count + 1);
            used[i] = false;
        }
}
void solve()
{
    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        cin >> a[i];
        ++ind[a[i][0]];
        ++rnd[a[i][a[i].length() - 1]];
    }
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            if (i != j && a[i][a[i].length() - 1] == a[j][0])
                e[i].push_back(j);
    for (int i = 1; i <= n; ++i)
        if (ind[a[i][0]] == rnd[a[i][0]] + 1)
        {
            used[i] = true;
            dfs(i, a[i] + '.', 1);
            used[i] = false;
        }
    used[1] = true;
    dfs(1, a[1] + '.', 1);
    used[1] = false;
    cout << "***";
    return ;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}