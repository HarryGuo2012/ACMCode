#include <cstdio>
#include <cstring>

#define MAX_N 100005

int sum[MAX_N];
int n;

int solve(){
	int now = sum[0], ans = -1;
	for(int i = 1; i <= n; i++){
		now += sum[i];
		if(now == i) ans = i;
	}
	return ans;
}

int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		memset(sum, 0, sizeof(sum));
		scanf("%d", &n);
		for(int i = 1; i <= n; i++){
			int a, b;
			scanf("%d%d", &a, &b);
			if(a <= n) sum[a]++;
			if(b + 1 <= n) sum[b + 1]--;
		}
		printf("%d\n", solve());
	}
	return 0;
}