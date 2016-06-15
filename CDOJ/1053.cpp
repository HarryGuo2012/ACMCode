#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

#define MAX_N 100005

bool check[MAX_N];
int mu[MAX_N], prime[MAX_N], tot = 0;

std::vector<int> G[MAX_N];

void Euler(){
	memset(check, 0, sizeof(check));
	mu[1] = 1;
	for(int i = 2; i < MAX_N; i++){
		if(!check[i]){
			prime[tot++] = i;
			mu[i] = -1;
		}
		for(int j = 0; j < tot; j++){
			if(i * prime[j] >= MAX_N) break;
			check[i * prime[j]] = true;
			if(i % prime[j] == 0){
				mu[i * prime[j]] = 0;
				break;
			}
			else
				mu[i * prime[j]] = - mu[i];
		}
	}
}

typedef long long ll;

const ll mod = 1000000007;

ll Pow(ll a, ll x){
	ll res = 1;
	while(x){
		if(x & 1) res = res * a % mod;
		a = a * a % mod;
		x >>= 1;
	}
	return res;
}

ll inv(ll a){
	return Pow(a, mod - 2);
}

void add(ll &a, ll x){
	a = (a + x) % mod;
	a = (a + mod) % mod;
}

ll ans[MAX_N];

struct node{
	ll cnt, d;
	node(){cnt = 0; d = 0;}
	node(int dd, int cc) : d(dd), cnt(cc){}
}f[MAX_N];

bool cmp(node x, node y){
	return x.cnt > y.cnt;
}

ll cnt[MAX_N], a[MAX_N];
int n;

ll fac[MAX_N];

ll C(ll x, ll k){
	return fac[x] * inv(fac[k]) % mod * inv(fac[x - k]) % mod;
}

int main(){
	for(int i = 1; i < MAX_N; i++)
		for(int j = i; j < MAX_N; j += i)
			G[j].push_back(i);
	fac[0] = 1;
	for(int i = 1; i < MAX_N; i++)
		fac[i] = i * fac[i - 1] % mod;
	Euler();
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		int t;
		scanf("%d", &t);
		a[t]++;
	}
	for(int i = 1; i <= n; i++)
		for(int j = i; j <= n; j += i)
			cnt[i] += a[j];
	for(int i = 1; i <= n; i++)
		f[i] = node(i, cnt[i]);
	std::sort(f + 1, f + 1 + n, cmp);

	for(int k = 1; k < n; k++){
		for(int i = 1; i <= n; i++){
			if(f[i].cnt < k) break;
			ll tmp = 0;
			for(auto t : G[f[i].d]){
				if(f[i].d / t <= n - k)
					add(tmp, mu[t]);
			}
			//printf("%d\n", tmp);
			add(ans[k], tmp * C(f[i].cnt, k) % mod);
		}
	}
	for(int k = 1; k < n; k++)
		printf("%lld\n", ans[k]);
	return 0;
}