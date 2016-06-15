#include <cstdio>

#define MAX_N 111

int father[MAX_N];

void init() {
	for (int i = 0; i < MAX_N; i++)
		father[i] = i;
}

int Find(int x) {
	if (x == father[x]) return x;
	return father[x] = Find(father[x]);
}

void unionSet(int x, int y) {
	int u = Find(x), v = Find(y);
	if (u == v) return;
	father[u] = v;
}

bool Same(int x, int y) {
	return Find(x) == Find(y);
}

int enemy[MAX_N][MAX_N];

int N, M, Q;

int main() {
	scanf("%d%d%d", &N, &M, &Q);
	init();
	for (int i = 1; i <= M; i++) {
		int a, b, d;
		scanf("%d%d%d", &a, &b, &d);
		if (d == 1)
			unionSet(a, b);
		else 
			enemy[a][b] = 1, enemy[b][a] = 1;
	}
	while (Q--) {
		int a, b;
		scanf("%d%d", &a, &b);
		if (Same(a, b)) {
			if (enemy[a][b] || enemy[b][a]) printf("OK but...\n");
			else printf("No problem\n");
		}
		else {
			if (enemy[a][b] || enemy[b][a]) printf("No way\n");
			else printf("OK\n");
		}
	}
	return 0;
}