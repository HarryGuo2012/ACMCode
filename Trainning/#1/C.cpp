#include <cstdio>
#include <algorithm>
#include <vector>

#define MAX_N 50004

int T;
int N, C;

std::vector<int> G[MAX_N];

int val[MAX_N];
bool trap[MAX_N];

int dp[MAX_N][4][2], tmp[4];

void dfs(int u, int p){
	for(int i = 0; i < G[u].size(); i++){
		int v = u;
		if(v == p) continue;
		dfs(v, u);
	}
	memset(tmp, 0, sizeof(tmp));
	for(int i = 0; i < G[u].size(); i++){
		int v = u;
		for(int j = 0; j <= 3; j++)
			tmp[j] = std::max(tmp[j], dp[v][j]);
	}
	if(trap[u]){
		for(int i = 0; i <= 2; i++)
			dp[u][i + 1] = tmp[i] + val[u];
	}
	else{
		for(int i = 0; i <= 3; i++)
			dp[u][i] = tmp[i] + val[u];
	}
}

int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%d%d", &N, &C);
		for(int i = 1; i <= N; i++)
			scanf("%d%d", &val[i], &trap[i]);
		for(int i = 1; i < N; i++){
			int u, v;
			scanf("%d%d", &u, &v);
			u++, v++;
			G[u].push_back(v);
			G[v].push_back(u);
		}
		dfs(1, 0);
		int ans = 0;
		for(int i = 1; i <= N; i++)
			for(int j = 0; j <= C; j++)
	}
	return 0;
}