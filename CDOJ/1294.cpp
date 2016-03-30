#include <cstdio>

#define MAX_D 20

typedef long long ll;

int N;

ll cnt[1 << MAX_D], dp[1 << MAX_D];

const ll mod = 1000000007;

void add(ll &x, ll a){
	x = ((x + a) % mod + mod) % mod;
}

ll Pow(ll a, ll x){
	ll res = 1;
	while(x){
		if(x & 1)res = res * a % mod;
		a = a * a % mod;
		x >>= 1;
	}
	return res;
}

int main(){
	scanf("%d", &N);
	for(int i = 0; i < N; i++){
		int a;
		scanf("%d", &a);
		a ^= (1 << MAX_D) - 1;
		add(cnt[a], 1);
	}
	
	for(int i = 0; i < MAX_D; i++)
		for(int mask = 0; mask < (1 << MAX_D); mask++){
			if(mask >> i & 1)continue;
			add(cnt[mask | (1 << i)], cnt[mask]);
		}
		
	for(int mask = 0; mask < (1 << MAX_D); mask++)
		dp[mask] = Pow(2, cnt[mask]);
	
	for(int i = 0; i < MAX_D; i++)
		for(int mask = 0; mask < (1 << MAX_D); mask++){
			if(mask >> i & 1)continue;
			add(dp[mask | (1 << i)], -dp[mask]);
		}
	printf("%lld\n", dp[(1 << MAX_D) - 1]);
	return 0;
}