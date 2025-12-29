#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int MAXN = 405;
vector<int> tree[MAXN];
int sub[MAXN];
bool visited[MAXN];
int n, m;

void dfs(int node, int parent)
{
    sub[node] = 1;
    for (int child : tree[node])
    {
        if (child != parent)
        {
            dfs(child, node);
            sub[node] += sub[child];
        }
    }
}

bool can_win()
{
    dfs(1, -1);
    for (int i = 1; i <= n; ++i)
    {
        if (sub[i] >= m + 3)
        {
            return 1;
        }
    }
    return 0;
}

int main()
{
    cin >> n >> m;
    for (int i = 0; i < n - 1; ++i)
    {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    if (can_win())
    {
        cout << "YES" << endl;
    }
    else
    {
        cout << "NO" << endl;
    }

    return 0;
}
