#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>

#define MAX_N 2000006

int a[MAX_N], N;
int sum[MAX_N];
int st[MAX_N][30]; //DP数组
void initRMQIndex() {
	for (int i = 1; i <= N; i++)		st[i][0] = i;
	for (int j = 1; (1 << j) <= N; j++)
		for (int i = 1; i + (1 << j) - 1 <= N; i++)
			st[i][j] = sum[st[i][j-1]] <= sum[st[i+(1<<(j-1))][j-1]] ? 
									st[i][j-1] : st[i+(1<<(j-1))][j-1];
}

int RMQIndex(int s, int v) {
	int k = int(log(v-s+1.0) / log(2.0));
	return sum[st[s][k]] <= sum[st[v-(1<<k)+1][k]] ? st[s][k] : st[v-(1<<k)+1][k];
}

int K;

int main() {
	scanf("%d%d", &N, &K);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &a[i]);
		a[i + N] = a[i];
	}
	for (int i = 1; i <= 2 * N; i++)
		sum[i] = sum[i - 1] + a[i];
	initRMQIndex();
	int x = sum[1], L = 1, R = 1;
	for (int i = 2; i <= N; i++) {
		int t = RMQIndex(0, i - 1);
		if (i > K) t = RMQIndex(i - K, i - 1);
		
		if (x == sum[i] - sum[t]) {
			if (t + 1 < L) {
				L = t + 1;
				R = i;
				x = sum[i] - sum[t];
			}
		}
		else if (x < sum[i] - sum[t]) {
			x = sum[i] - sum[t];
			L = t + 1;
			R = i;
		}
	}
	for (int i = 1; i <= K; i++) {
		int t = RMQIndex
	}
	printf("%d %d %d\n", x, L, R);
	return 0;
}