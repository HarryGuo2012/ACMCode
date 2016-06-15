#include <cstdio>

#define MAX_N 1000006

int n, m;
int ans[MAX_N];

int main() {
	int a = 0, b = 1;
	scanf("%d%d", &n, &m);
	while (m--) {
		int t, x;
		scanf("%d", &t);
		if (t == 1) {
			scanf("%d", &x);
			a += x;
			b += x;
		}		
		else {
			if (a & 1) a--;
			else a++;
			if (b & 1) b--;
			else b++;
		}
		a  = (a + n) % n;
		b  = (b + n) % n;
	}
	//printf("%d %d\n", a, b);
	for (int i = 0; i < n; i += 2) 
		ans[(a + i) % n] = i;
	for (int i = 1; i < n; i += 2)
		ans[(b + i - 1) % n] = i;
	for (int i = 0; i < n; i++)
		printf("%d ", ans[i] + 1);
	printf("\n");
	return 0;
}