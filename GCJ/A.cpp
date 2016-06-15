#include <cstdio>

int T;

typedef long long ll;

int main(){
	freopen("A.txt", "w", stdout);
	ll N;
	scanf("%d", &T);
	int cas = 0;
	while(T--){
		scanf("%lld", &N);
		printf("Case #%d: ", ++cas);
		if(N == 0){
			printf("INSOMNIA\n");
			continue;
		}
		ll mask = 0;
		ll now = 0;
		while(mask < (1ll << 10) - 1){
			now += N;
			ll x = now;
			while(x){
				mask |= (1ll << (x % 10));
				x /= 10;
			}
		}
		printf("%lld\n", now);
	}
	return 0;
}