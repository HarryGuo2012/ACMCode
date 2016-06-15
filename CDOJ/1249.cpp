#include <cstdio>
#include <algorithm>
#include <climits>
#include <queue>
#include <vector>

#define MAX_N 2222

typedef std::pair<int, int> P;

int G[MAX_N][MAX_N];
int n, m;

bool used[MAX_N];

void unionST(int s, int t){
	used[s] = 1;
	for(int i = 1; i <= n; i++){
		if(i == t) continue;
		G[t][i] += G[s][i];
		G[i][t] += G[i][s];
	}
}

std::priority_queue<P> que;
bool vis[MAX_N];
std::vector<int> nodeInOrder;

P FindST(){
	while(que.size()) que.pop();
	nodeInOrder.clear();
	for(int i = 1; i <= n; i++)
		vis[i] = 0;
	vis[1] = 1;
	que.push(std::make_pair(0, 1));
	while(que.size()){
		int u = que.top().second;
		que.pop();

		nodeInOrder.push_back(u);
		for(int v = 1; v <= n; v++){
			if(!used[v] && !vis[v] && G[u][v]){
				vis[v] = 1;
				que.push(std::make_pair(G[u][v], v));
			}
		}
	}
	return std::make_pair(*(nodeInOrder.rbegin() + 1), *(nodeInOrder.rbegin()));
}

int Stoer_Wagner(){
	int ans = INT_MAX;
	for(int i = 1; i < n; i++){
		P p = FindST();
		int s = p.first, t = p.second;
		int sum = 0;
		for(int j = 1; j <= n; j++)
			if(!used[j])
				sum += G[t][j];
		ans = std::min(ans, sum);
		if(ans == 0)
			return ans;
		unionST(s, t);
	}
	return ans;
}

int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++){
		int u, v, c;
		scanf("%d%d%d", &u, &v, &c);
		G[u][v] += c;
		G[v][u] += c;
	}
	printf("%d\n", Stoer_Wagner());
	return 0;
}