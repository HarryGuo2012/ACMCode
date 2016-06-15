#include <cstdio>
#include <algorithm>
#include <cstring>

#define N 18
#define MAX_S (1 << 18)
#define MAX_T 9

int S, dp[MAX_S][MAX_T + 1], beginPoints;

int contain(int mask, int i, int j, int k) {
	return (mask >> i & 1) && (mask >> j & 1) && (mask >> k & 1);
}

int count(int mask) {
	int res =
		contain(mask, 0, 1, 2) +
		contain(mask, 3, 4, 5) + contain(mask, 2, 4, 6) + contain(mask, 6, 7, 8) +
		contain(mask, 9, 10, 11) + contain(mask, 5, 10, 12) + contain(mask, 12, 13, 14) + contain(mask, 8, 13, 15) + contain(mask, 15, 16, 17);
	return res;
}

int greedy(int mask) {
	bool update = true;
	while (update) {
		update = false;
		for (int i = 0; i < N; i++)
			if (count(mask) < count(mask | (1 << i))) {
				update = true;
				mask |= (1 << i);
			}
	}
	return mask;
}

void dfs(int mask, int points) {
	if (dp[mask][points] != -1) return;
	int newMask = greedy(mask), state = 3;
	for (int i = 0; i < N; i++)
		if (!(newMask >> i & 1)) {
			int opponentPoints = count(mask) - points - beginPoints;
			dfs(newMask | (1 << i), opponentPoints);
			state = std::min(state, dp[newMask | (1 << i)][opponentPoints]);
		}
	if (newMask == MAX_S - 1) state = std::min(state, dp[newMask][count(mask) - points - beginPoints]);
	dp[mask][points] = 2 - state;
}

int M;

int main() {
	scanf("%d", &M);
	for (int i = 0; i < M; i++) {
		int a;
		scanf("%d", &a);
		S |= (1 << (a - 1));
	}
	beginPoints = count(S);
	memset(dp, -1, sizeof(dp));
	for (int i = 0; i <= MAX_T; i++) {
		int j = MAX_T - i - beginPoints;
		if (i > j) dp[MAX_S - 1][i] = 2;
		if (i == j) dp[MAX_S - 1][i] = 1;
		if (i < j) dp[MAX_S - 1][i] = 0;
	}
	dfs(S, 0);
	if (dp[S][0] == 2) printf("WIN!\n");
	if (dp[S][0] == 1) printf("Draw\n");
	if (dp[S][0] == 0) printf("LOSE!\n");
	return 0;
}