#include <cstdio>
#include <vector>
#include <set>
#define MAX_N 300005

typedef long long ll;

ll ans = 0;

int n, m;
int a[MAX_N], pos[MAX_N];
std::vector<int> G[MAX_N];
int foe[MAX_N];

std::set<pair<int,int> > se;

int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++)
		pos[a[i]] = i;

	for(int i = 1; i <= m; i++){
		int x, y;
		scanf("%d%d", &x, &y);
		if(se.find(make_pair(x, y)) != se.end()) continue;
		se.insert(make_pair(x, y));
		G[x].push_back(y);
		G[y].push_back(x);
	}

	int l = 1, r = 1;
	for(auto u : G[1])
		foe[u] = 1;
	in[1] = 1;
	int cnt = 0;
	while(r <= n){
		while(cnt){
			for(auto u : G[l]){
				if(!in[u]) continue;
				foe[u]--;
				if(foe[u] == 0) cnt--;
			}
			in[l++] = 0;
		}
		ans += ((ll)r - l + 1);
		if(r == n)break;
		r++;
		in[r] = 1;
		for(auto u : G[r]){
			if(!in[u]) continue;
			foe[u]++;
			if(foe[u] == 1) cnt++;
			foe[r]++;
		}
	}
	printf("%I64d\n", ans);
	return 0;
}