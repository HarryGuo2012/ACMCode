#include <cstdio>
#include <algorithm>
#include <cstring>

#define MAX_N 10004

struct node {
	int income;
	int redBag;
	int id;
}A[MAX_N];

bool cmp(node a, node b) {
	if (a.income == b.income) {
		if (a.redBag == b.redBag)
			return a.id < b.id;
		return a.redBag > b.redBag;
	}
	return a.income > b.income;
}

int N;

int main() {
	scanf("%d", &N);
	memset(A, 0, sizeof(A));
	for (int i = 1; i <= N; i++) {
		A[i].id = i;
		int K;
		scanf("%d", &K);
		for (int j = 0; j < K; j++) {
			int p, c;
			scanf("%d%d", &p, &c);
			A[p].income += c;
			A[i].income -= c;
			A[p].redBag++;
		}
	}
	std::sort(A + 1, A + 1 + N, cmp);
	for (int i = 1; i <= N; i++) 
		printf("%d %.2f\n", A[i].id, A[i].income / 100.0);
	return 0;
}