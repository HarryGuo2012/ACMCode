#include <cstdio>
#include <cstring>

#define MAX_N 1000006

bool check[MAX_N];
int mu[MAX_N], prime[MAX_N], tot = 0;

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

ll f[MAX_N];

int main(){
	Euler();
	int T;
	scanf("%d", &T);
	while(T--){
		int n;
		scanf("%d", &n);
		ll ans = 0;
		memset(f, 0, sizeof(f));
		for(int i = 1; i <= n; i++)
			for(int j = i; j <= n; j += i)
				f[i]++;
		ll tmp = 0;
		for(int d = 1; d <= n; d++){
			ans += mu[d] * f[d] * f[d] * f[d];
			tmp += mu[d] * f[d] * f[d];
		}
		printf("%lld\n", ans + 3 * tmp + 3);
	}
	return 0;
}