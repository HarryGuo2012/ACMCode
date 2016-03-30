#include <cstdio>
#include <set>
#include <cstring>
#include <vector>

#define MAX_N 100005
#define MAX_A 1000006
#define MAX_D 21

int prime[MAX_A], tot=0;
bool check[MAX_A];

void Euler() {
	memset(check, 0, sizeof(check));
	for (int i = 2; i < MAX_A; i++) {
		if (!check[i])prime[tot++] = i;
		for (int j = 0; j < tot; j++) {
			if (prime[j] * i >= MAX_A)break;
			check[prime[j] * i] = 1;
			if (i % prime[j] == 0)break;
		}
	}
}

int T, n;

int cnt[MAX_A][MAX_D];

std::set<int> se;
bool vis[MAX_A];

void divide(int a){
	for(int i = 0; i < tot; i++){
		if(prime[i] * prime[i] > a)
			break;
		int tmp = 0;
		while(a % prime[i] == 0){
			if(!vis[prime[i]])
				se.insert(prime[i]);
			vis[prime[i]] = 1;
			tmp++;
			a /= prime[i];
		}
		if(tmp)
			cnt[prime[i]][tmp]++;
	}
	if(a != 1) {
		cnt[a][1]++;
		se.insert(a);
	}
}

std::vector<int> v;

const long long mod = 1000000007;

long long Pow(long long a, long long x){
	long long res = 1;
	while(x){
		if(x & 1) res = res * a % mod;
		a = a * a % mod;
		x >>= 1;
	}
	return res;
}

std::vector<long long> ans;

int maxd[MAX_A];

int main(){
	Euler();
	scanf("%d", &T);
	while(T--){
		ans.clear();
		memset(vis, 0, sizeof(vis));
		memset(cnt, 0, sizeof(cnt));
		se.clear();

		for(int i = 0; i < MAX_A; i++)
			maxd[i] = 20;

		scanf("%d", &n);
		for(int i = 0; i < n; i++){
			int a;
			scanf("%d", &a);
			divide(a);
		}

		while(ans.size() != n && se.size()){
			long long now = 1;
			v.clear();
			int t = MAX_N + 5;

			for(auto u : se){
				int p = 0;
				while(cnt[u][maxd[u]] == 0) maxd[u]--;
				p = maxd[u];

				t = std::min(t, cnt[u][p]);
			}
			for(auto u : se){
				int p = maxd[u];

				cnt[u][p] -= t;
				now = now * Pow(u, p) % mod;
			}
			for(int i = 0; i < t; i++)
				ans.push_back(now);

			for(auto u : se){
				while(maxd[u] > 0 && cnt[u][maxd[u]] == 0) maxd[u]--;
				int p = maxd[u];
				if(p == 0)
					v.push_back(u);
			}
			for(auto u : v)
				se.erase(u);
		}
		while(ans.size() != n) ans.push_back(1);
		for(auto u : ans)
			printf("%lld ", u);
		printf("\n");
	}
	return 0;
}