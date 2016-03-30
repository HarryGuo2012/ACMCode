#include <cstdio>

#define MAX_N 100005
#define MAX_D 55

typedef long long ll;

ll cnt[MAX_D][2];
int n;

ll ans = 0;

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		ll a;
		scanf("%lld", &a);
		for(int j = 0; j < MAX_D; j++){
			if((a >> j) & 1){
				ans += cnt[j][0] * (1ll << j);
				ans += cnt[j][1] * (1ll << j);
				ans += (cnt[j][0] + cnt[j][1]) * (1ll << j);
				cnt[j][1]++;
			}
			else{
				ans += cnt[j][1] * (1ll << j);
				ans += cnt[j][1] * (1ll << j);
				cnt[j][0]++;
			}
		}
	}
	printf("%lld\n", ans);
	return 0;
}