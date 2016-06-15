#include <cstdio>
#define MAX_N 10
#define MAX_S 10000
using namespace std;

int a[MAX_N];
int n;

int tot = 0;

int abs(int x) {
	return x < 0 ? -x : x;
}

bool check(int x, int b) {
	for (int i = 1; i < x; i++) {
		if (a[i] == b) return false;
		if (abs(a[i] - b) == abs(i - x)) return false;
	}
	return true;
}

int ans[MAX_S][MAX_N];

void dfs(int x) {
	if (x == n + 1) {
		tot++;
		for (int i = 1; i <= n; i++)
			ans[tot][i] = a[i];
		return;
	}
	for (int i = 1; i <= n; i++) 
		if (check(x, i)) {
			a[x] = i;
			dfs(x + 1);
		}
}

int main() {
	scanf("%d", &n);
	dfs(1);
	printf("%d\n", tot);
	for (int i = 1; i <= tot; i++) {
		for (int j = 1; j <= n; j++) {
			printf("%d ", ans[i][j]);
		}
		printf("\n");
	}
	return 0;
}