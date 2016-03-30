#include <cstring>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
using namespace std;
#define MAX_N 55

int G[MAX_N][MAX_N];

int ans = 1008611;

int vis[MAX_N];
queue<int> que;
int n;

bool inQue[MAX_N];

void bfs(int u, int v){
	memset(vis, 0, sizeof(vis));
	memset(inQue, 0, sizeof(inQue));
	vis[u] = 1;
	vis[v] = 1;
	inQue[u] = 1;
	inQue[v] = 1;
	que.push(u);que.push(v);
	while(que.size()){
		int now = que.front();que.pop();
		inQue[now] = 0;
		for(int i = 0; i < n; i++){
			if(vis[i]){
				int t = G[now][i];
				if(!vis[t]){
					vis[t]=1;
					if(!inQue[t]){
						inQue[t] = 1;
						que.push(t);
					}
				}
			}
		}
	}	
	int cnt = 0;
	for(int i = 0; i < n; i++)
		if(vis[i])cnt++;
	ans = min(ans, cnt);
}

class MultiplicationTable2{
public:
	int minimalGoodSet(vector <int> table){
		for(n = 0; n * n < table.size(); n++);
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
				G[i][j] = table[i * n + j];
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
				bfs(i, j);
		return ans;
	}
};