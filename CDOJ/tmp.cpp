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

std::set<std::pair<int,int> > se;

bool in[MAX_N];

int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++)
		pos[a[i]] = i;

	for(int i = 1; i <= m; i++){
		int x, y;
		scanf("%d%d", &x, &y);
		if(se.find(std::make_pair(x, y)) != se.end()) continue;
		se.insert(std::make_pair(x, y));
		se.insert(std::make_pair(y, x));
		G[x].push_back(y);
		G[y].push_back(x);
	}

	int l = 1, r = 1;
	for(auto u : G[a[1]])
		foe[u] = 1;
	in[a[1]] = 1;
	int cnt = 0;
	while(r <= n){
		while(cnt){
			for(auto u : G[a[l]]){
				if(!in[u]) continue;
				foe[u]--;
				if(foe[u] == 0) cnt--;
			}
			in[a[l]] = 0;
			l++;
		}
		//printf("%d %d\n", l, r);
		ans += ((ll)r - l + 1);
		if(r == n)break;
		r++;
		in[a[r]] = 1;
		for(auto u : G[a[r]]){
			if(!in[u]) continue;
			foe[a[r]]++;
			cnt++;
		}
	}
	printf("%I64d\n", ans);
	return 0;
}