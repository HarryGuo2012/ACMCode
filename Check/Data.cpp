#include <cstdio>
#include <cstdlib>
#include <ctime>

int main() {
	srand(time(0));
	int n = rand() % 5 + 1, m = rand() % 10;
	printf("%d %d\n", n, m);
	for (int i = 0; i < n; i++) {
		int t = rand() % 3;
		if (t == 0) printf("AND ");
		if (t == 1) printf("OR ");
		if (t == 2) printf("XOR ");
		printf("%d\n", rand() % 10);
	}
	return 0;
}