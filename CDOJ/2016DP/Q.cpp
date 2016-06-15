#include <cstdio>
#include <algorithm>

typedef long long ll;

#define MAX_N 500005
#define INF 1234567890

int N, M, A[MAX_N], que[MAX_N];
ll S[MAX_N], dp[MAX_N];

double X(int t) {
	return 2 * S[t];
}

double Y(int t) {
	return dp[t] + (double)S[t] * S[t];
}

double Slope(int u, int v) {
	if (X(u) == X(v)) return INF;
	return (Y(u) - Y(v)) / (X(u) - X(v));
}

int main() {
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; i++)
		scanf("%d", &A[i]);
	for (int i = 1; i <= N; i++)
		S[i] = S[i - 1] + A[i];
	int front = 0, rear = 0;
    que[rear++] = 0;

    for (int i = 1; i <= N; i++) {
        while (rear - front > 1 && Slope(que[front], que[front + 1]) <= S[i])front++;
        int j = que[front];
        dp[i] = dp[j] + (S[i] - S[j]) * (S[i] - S[j]) + M;
        while (rear - front > 1 && Slope(que[rear - 1], que[rear - 2]) >= Slope(que[rear - 1], i))rear--;
        que[rear++] = i;
    }
    printf("%lld\n", dp[N]);
	return 0;
}