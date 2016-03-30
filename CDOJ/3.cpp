#include <cstdio>
#include <cstring>

#define MAX_N 100005

int T;

long long a[MAX_N];
long long sum[MAX_N];

void solve(int n, int m){
	memset(sum, 0, sizeof(sum));
	long long now = 0, ans = 0;

	for(int i = 1; i <= n; i++){
		now -= sum[i];
		long long d = a[i] - now;
		if(d < 0) continue;
		ans += d;
		sum[i + m] += d;
		now += d;
	}

	printf("%lld\n", ans);
}

int main(){
	scanf("%d", &T);
	int cas = 0;
	while(T--){
		int n, m;
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		printf("Case #%d: ", ++cas);
		solve(n, m);
	}
	return 0;
}