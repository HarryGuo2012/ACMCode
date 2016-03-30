#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#include <queue>

#define MAX_N 112
#define MAX_S 112 * 265 * 54

typedef std::pair<int, int> P;

int lh, ls, n, d[MAX_N];

std::vector<int> G[MAX_S];

int Hash(int hp, int sp, int enemy){
	return enemy * (105 * 255) + hp * (105) + sp;
}

void init(){
	for(int i = 0; i <= lh + 1; i++)
		for(int j = 0; j <= ls + 1; j++)
			for(int k = 0; k <= n + 1; k++)
				G[Hash(i, j, k)].clear();
}

int getSp(int x){
	return std::min(x, ls);
}

void build(){
	for(int i = 1; i <= lh; i++)
		for(int j = 0; j <= ls; j++)
			for(int k = 1; k <= n; k++){
				int u = Hash(i, j, k), v;

				if(i > k - 1){
					v = Hash(i - (k - 1), getSp(j + 1 + (k - 1) % 3), k - 1);
					if(u != v)
						G[u].push_back(v);
				}

				if(std::min(lh, i + lh / 5) > k){
					v = Hash(std::min(lh, i + lh / 5) - k, getSp(j + k % 3), k);
					if(u != v)
						G[u].push_back(v);
				}

				if(i > k - d[j] && j > 0){
					v = Hash(i - std::max(k - d[j], 0), getSp(std::max(k - d[j], 0) % 3), std::max(k - d[j], 0));
					if(u != v) 
						G[u].push_back(v);
				}

				if(i > k){
					v = Hash(i - k, getSp(j + k % 3), k);
					if(u != v) 
						G[u].push_back(v);
				}
			}
}

std::queue<int> que;
int dis[MAX_S];

int bfs(int s){
	while(que.size()) que.pop();
	memset(dis, -1, sizeof(dis));
	dis[s] = 0;
	que.push(s);

	while(que.size()){
		int u = que.front();
		que.pop();
		for(auto v : G[u])
			if(dis[v] == -1){
				dis[v] = dis[u] + 1;
				que.push(v);
			}
	}

	int ans = -1;

	for(int i = 1; i <= lh; i++)
		for(int j = 0; j <= ls; j++){
			int u = Hash(i, j, 0);
			if(dis[u] != -1)
				ans = dis[u];
		}
	return ans;
}

int main(){
	while(scanf("%d%d%d", &lh, &ls, &n) == 3){
		for(int i = 1; i <= ls; i++)
			scanf("%d", &d[i]);
		init();
		build();
		int ans = bfs(Hash(lh, 0, n));
		if(ans == -1)
			printf("HELP!\n");
		else
			printf("%d\n", ans);
	}
	return 0;
}