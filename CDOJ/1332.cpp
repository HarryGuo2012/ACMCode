#include <cstdio>
#include <algorithm>
#include <vector>

#define MAX_N 33

std::vector<int> G[MAX_N];
int N, M;

bool vis[MAX_N];
std::vector<int> nodes[2];

int id[MAX_N];

void dfs(int u, int c){
	id[u] = nodes[c].size();
	nodes[c].push_back(u);
	vis[u] = 1;
	for(auto v : G[u])
		if(!vis[v]) 
			dfs(v, !c);
}

std::vector<int> inactivated;
int control[2][MAX_N];

typedef long long ll;

ll dp[1 << 15];

std::vector<int> newMasks;
bool cmp(int x, int y){
	if(__builtin_popcount(x) == __builtin_popcount(y))
		return x < y;
	return __builtin_popcount(x) < __builtin_popcount(y);
}

int main(){
	scanf("%d%d", &N, &M);
	for(int i = 0; i < M; i++){
		int u, v;
		scanf("%d%d", &u, &v);
		u--, v--;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	for(int u = 0; u < N; u++)
		if(!vis[u])
			dfs(u, 0);
	if(nodes[0].size() > nodes[1].size())
		std::swap(nodes[0], nodes[1]);

	for(auto u : nodes[0])
		for(auto v : G[u])
			control[0][u] |= (1 << id[v]);
	for(auto u : nodes[1])
		for(auto v : G[u])
			control[1][u] |= (1 << id[v]);
	long long ans = 0;

	for(int mask = 0; mask < (1 << nodes[0].size()); mask++){
		int rightMask = 0, leftMask = mask;
		for(int i = 0; i < nodes[0].size(); i++)
			if(mask >> i & 1)
				rightMask |= control[0][nodes[0][i]];
		for(int i = 0; i < nodes[1].size(); i++)
			if(!(rightMask >> i & 1))
				leftMask |= control[1][nodes[1][i]];
		inactivated.clear();

		int rightForceToOne = nodes[1].size() - __builtin_popcount(rightMask);

		for(int i = 0; i < nodes[0].size(); i++)
			if(!(leftMask >> i & 1))
				inactivated.push_back(nodes[0][i]);
		//printf("%d\n", inactivated.size());
		newMasks.clear();
		for(int newMask = 0; newMask < (1 << inactivated.size()); newMask++)
			newMasks.push_back(newMask);
		std::sort(newMasks.begin(), newMasks.end(), cmp);
		for(auto newMask : newMasks){
			int dominate = (1 << nodes[1].size()) - 1;
			for(int i = 0; i < inactivated.size(); i++){
				if(!(newMask >> i & 1))
					dominate ^= dominate & control[0][inactivated[i]];
			}

			bool flag = true;
			int cnt = N - nodes[0].size() - rightForceToOne, tmp = newMask;
			for(int i = 0; i < inactivated.size(); i++){
				if(newMask >> i & 1){
					int check = control[0][inactivated[i]] & dominate;
					if(!check){
						flag = false;
						tmp ^= 1 << i;
					}
				}
			}
			cnt -= nodes[1].size() - __builtin_popcount(dominate);
			if(!flag)
				dp[newMask] = dp[tmp];
			else
				dp[newMask] = 1 << cnt;
			//printf("%d %d\n", newMask, dp[newMask]);
		}
		for(int i = 0; i < inactivated.size(); i++)
			for(int newMask = 0; newMask < (1 << inactivated.size()); newMask++){
				if(newMask >> i & 1) continue;
				//printf("%d\n", newMask | (1 << i));
				dp[newMask | (1 << i)] -= dp[newMask];
			}
		//printf("%d\n", dp[(1 << inactivated.size()) - 1]);
		ans += dp[(1 << inactivated.size()) - 1];
	}
	printf("%lld\n", ans);
	return 0;
}