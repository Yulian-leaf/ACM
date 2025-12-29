//dij
#include <iostream>
#include <cstring>
using namespace std;
int map[120520][120520];
int vis[520520], bef[520520], dis[520520];
int n, m, s;

void dij() {
	int t = s;
	vis[t] = 1;
	for (int i = 1; i <= n; i++) {
		dis[i] = map[i][t];
	}
	while (1) {
		int minn = 1e9;
		int temp = t;
		for (int i = 1; i <= n; i++) {
			if (vis[i] == 0 && map[t][i] < minn) {
				minn = map[t][i];
				temp = i;
			}
		}
		if (temp == t)
			break;
		vis[temp] = 1;
		for (int i = 1; i <= n; i++) {
			if (vis[i] == 0) {
				if (dis[temp] + map[temp][i] < dis[temp]) {
					dis[i] = dis[temp] + map[temp][i];
					bef[i] = temp;
				}
			}
		}
		t = temp;
	}
	return ;
}

int main() {
	cin >> n >> m >> s;
	memset(map, 0x3f, sizeof(map));
	for (int i = 1; i <= m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		map[u][v] = w;
		map[v][u] = w;

	}
}