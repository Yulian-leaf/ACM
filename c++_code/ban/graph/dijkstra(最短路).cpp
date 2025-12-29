#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#define Inf 0x3f3f3f3f
using namespace std;
int map[1005][1005];
int vis[1005], dis[1005];
int n, m; //n¸öµã£¬mÌõ±ß
void Init () {
	memset(map, 0, sizeof(map));
	for (int i = 1; i <= n; i++) {
		map[i][i] = 0;
	}
}
void Getmap() {
	int u, v, w;
	for (int t = 1; t <= m; t++) {
		scanf("%d%d%d", &u, &v, &w);
		if (map[u][v] > w) {
			map[u][v] = w;
			map[v][u] = w;
		}
	}

}
void Dijkstra(int u) {
	memset(vis, 0, sizeof(vis));
	for (int t = 1; t <= n; t++) {
		dis[t] = map[u][t];
	}
	vis[u] = 1;
	for (int t = 1; t < n; t++) {
		int minn = Inf, temp;
		for (int i = 1; i <= n; i++) {
			if (!vis[i] && dis[i] < minn) {
				minn = dis[i];
				temp = i;
			}
		}
		vis[temp] = 1;
		for (int i = 1; i <= n; i++) {
			if (map[temp][i] + dis[temp] < dis[i]) {
				dis[i] = map[temp][i] + dis[temp];
			}
		}
	}

}
int main() {
	scanf("%d%d", &m, &n);
	Init();
	Getmap();
	Dijkstra(n);
	printf("%d\n", dis[1]);
	return 0;
}