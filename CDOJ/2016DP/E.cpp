#include <cstdio>
#include <algorithm>
#include <vector>

#define MAX_N 322

int N;

struct Matrix {
	const double eps = 1e-7;
	double A[MAX_N][MAX_N];
	double b[MAX_N];
	bool free[MAX_N];
	void add(int u, int v, double k) {
		for (int j = 1; j <= N; j++) 
			A[v][j] += A[u][j] * k;
		b[v] += b[u] * k;
	}

	void mult(int u, double k) {
		for (int j = 1; j <= N; j++)
			A[u][j] *= k;
		b[u] *= k;
	}

	void swapRow(int i, int j) {
		for (int k = 1; k <= N; k++)
			std::swap(A[i][k], A[j][k]);
		std::swap(b[i], b[j]);
	}

	int Gauss() {
		int cnt = 0;
		for (int i = 1; i <= N; i++) {
			int pos = i;
			while (pos <= N && fabs(A[pos][i]) < eps) pos++;
			if (pos == N + 1) {
				free[i] = 1;
				cnt++;
				continue;
			}
			swapRow(i, pos);
			mult(i, 1 / A[i][i]);
			for (int j = i + 1; j <= N; j++)
				add(i, j, -A[j][i]);
		}
		for (int i = N; i >= 1; i--) 
			if (!free[i])
				for (int j = i - 1; j >= 1; j--) 
					add(i, j, -A[j][i]);
		for (int i = 1; i <= N; i++)
			if (free[i] && fabs(b[i]) > eps) 
				return -1;
		return cnt;
	}
}mat;

int M;
int door[MAX_N];

int main() {
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= M; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		door[u] = v;
	}
	for (int i = 1; i <= N; i++) {
		mat.A[i][i] = 1;
		mat.b[i] = (i < N);
		for (int j = 1; j <= 6; j++) {
			int u = (i + j > N) ? i : i + j;
			if (door[u]) u = door[u];
			//printf("%d\n", u);
			mat.A[i][u] += -1.0 / 6.0;
		}
		//printf("----\n");
	}
	mat.A[N][N] = 1;
	int c = mat.Gauss();
	if (c == -1) printf("-1\n");
	else printf("%.7f\n", mat.b[1]);
	return 0;
}