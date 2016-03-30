#include <cstdio>
#define MAX_N 111

int k, n, m;
int a[MAX_N][MAX_N];
int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};

bool check(int x, int y){
	bool res = 0;
	for(int i = 0; i <= 4; i++){
		int u = dx[i] + x, v = dy[i] + y;
		if(u < 1 || u > n || v < 1 || v > m)continue;
		res |= a[u][v] & 1;
	}
	return res;
}

int main(){
	scanf("%d%d%d", &k, &n, &m);
	int o = 1, e = 2;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++){
			//printf("%d\n", check(i, j));
			if(check(i, j)){
				if(e <= k){
					a[i][j] = e;
					e += 2;
				}
				else a[i][j] = 0;
			}
			else{
				if(o <= k){
					a[i][j] = o;
					o += 2;
				}
				else a[i][j] = 0;
			}
		}
	if(o < k && e < k)
		printf("-1\n");
	else{
		for(int i = 1; i <= n; i++){
			for(int j = 1; j <= m; j++)
				printf("%d ", a[i][j]);
			printf("\n");
		}
	}
	return 0;
}