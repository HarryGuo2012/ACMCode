#include <cstdio>
#include <queue>

struct node {
	int L, R;
	node (int l, int r) : L(l), R(r) {}
	node () {}
};

std::queue<node> que;

int A[33], B[33];
int N;

bool vis[33];

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) 
		scanf("%d", &A[i]);
	for (int i = 1; i <= N; i++)
		scanf("%d", &B[i]);
	que.push(node(1, N));
	bool first = true;
	while (que.size()) {
		node now = que.front();
		que.pop();
		int p = -1;
		for (int i = 1; i <= N && p < 0; i++) {
			if (!vis[i]) {
				for (int j = now.L; j <= now.R; j++) 
					if (B[i] == A[j]) {
						vis[i] = 1;
						p = j;
						break;
					}
			}
		}
		
		if (first) printf("%d", A[p]);
		else printf(" %d", A[p]);
		first = false;
		if (now.R >= p + 1)
			que.push(node(p + 1, now.R));
		if (now.L <= p - 1)
			que.push(node(now.L, p - 1));
	}
	printf("\n");
	return 0;
}