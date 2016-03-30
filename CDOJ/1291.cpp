#include <cstdio>
#include <cstring>

#define MAX_N 200005
#define MAX_D 17
#define B 1024

const int mod = 1000000007;

void add(int &a, int b){
	a=(a+b)%mod;
}

int dp[MAX_N];
int table[1 << MAX_D];
int a[MAX_N];
int n, d;

char buff[MAX_D];

bool contain(int u, int v){
	return (u & v) == v;
}

int main(){
	scanf("%d%d", &n, &d);
	for(int i = 0; i < n; i++){
		scanf("%s", &buff);
		for(int j = 0; j < d; j++)
			a[i] |= (buff[j] == '1') << j;
	}
	int p = 0;
	for(int i = 0; i < n; i++){
		if(i % B == 0 || i == n - 1){
			for(int j = p; j <= i; j++)
				add(dp[j], 1);
			for(int j = p; j <= i; j++)
				for(int mask = 0; mask < (1 << d); mask++)
					if(contain(a[j], mask))
						add(dp[j], table[mask]);
			for(int j = p; j <= i; j++)
				for(int k = p; k < j; k++)
					if(contain(a[j], a[k]))
						add(dp[j], dp[k]);
			for(int j = p; j <= i; j++)
				add(table[a[j]], dp[j]);
			p = i + 1;
		}
	}
	int sum = 0;
	for(int i = 0; i < n; i++)
		add(sum, dp[i]);
	printf("%d\n", sum);
	return 0;
}