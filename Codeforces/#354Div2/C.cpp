#include <cstdio>
#include <cstring>
#include <algorithm>

#define MAX_N 100005

int n, k;
char s[MAX_N];

int sum[26][MAX_N];

void update(int &a, int x) {
	a = std::max(a, x);
}

void update2(int &a, int x) {
	a = std::min(a, x);
}

int Get(int L, int R) {
	int res = R - L + 1;
	for (int c = 0; c < 26; c++)
		update2(res, R - L + 1 - sum[c][R] + sum[c][L - 1]);
	return res;
}

int main() {
	scanf("%d%d%s", &n, &k, s + 1);
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < 26; j++) {
			if (j + 'a' == s[i])
				sum[j][i] = sum[j][i - 1] + 1;
			else
				sum[j][i] = sum[j][i - 1];
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		if (Get(i, n) <= k) 
			update(ans, n - i + 1);
		else {
			int L = i, R = n;
			while (R - L > 1) {
				int mid = (R + L) >> 1;
				if (Get(i, mid) <= k) L = mid;
				else R = mid;
			}
			update(ans, L - i + 1);
		}
	}
	printf("%d\n", ans);
	return 0;
}