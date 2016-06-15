#include <cstdio>

int n, m, q;

int a[111][111];

struct query {
	int t, x, y, z;
}Q[11111];

int main() {
	scanf("%d%d%d", &n, &m, &q);
	for (int i = 1; i <= q; i++) {
		scanf("%d%d", &Q[i].t, &Q[i].x);
		if (Q[i].t == 3) scanf("%d%d", &Q[i].y, &Q[i].z);
	}

	for (int k = q; k >= 1; k--) {
		if (Q[k].t == 3) a[Q[k].x][Q[k].y] = Q[k].z;
		if (Q[k].t == 1) {
			int tmp = a[Q[k].x][m];
			for (int j = m; j >= 2; j--) a[Q[k].x][j] = a[Q[k].x][j - 1];
			a[Q[k].x][1] = tmp;
		}
		if (Q[k].t == 2) {
			int tmp = a[n][Q[k].x];
			for (int i = n; i >= 2; i--) a[i][Q[k].x] = a[i - 1][Q[k].x];
			a[1][Q[k].x] = tmp;
		}
	}

	for (int i = 1; i <= n; i++, printf("\n"))
		for (int j = 1; j <= m; j++)
			printf("%d ", a[i][j]);

	return 0;
}