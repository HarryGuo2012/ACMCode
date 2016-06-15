#include <cstdio>

#define MAX_N 12

double a[MAX_N][MAX_N];

int n, t;

void dfs(int i, int j, double s) {
	if (i > n) return;
	if (a[i][j] + s > 1 || a[i][j] == 1) {
		double tmp = a[i][j] + s - 1;
		a[i][j] = 1;
		dfs(i + 1, j, tmp / 2);
		dfs(i + 1, j + 1, tmp / 2);
	}
	else 
		a[i][j] += s;
}

int main() {
	scanf("%d%d", &n, &t);
	for (int i = 1; i <= t; i++) 
		dfs(1, 1, 1);
	int cnt = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (a[i][j] == 1)
				cnt++;
	printf("%d\n", cnt);
	return 0;
}