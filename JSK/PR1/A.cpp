#include <cstdio>
#include <algorithm>

int T;

int a[27];

int main() {
	scanf("%d", &T);
	while (T--) {
		for (int i = 1; i <= 26; i++) 
			scanf("%d", &a[i]);
		std::sort(a + 1, a + 27);
		int p = 1;
		while (p <= 26 && a[p] == 0) p++;
		if (p > 26) 
			printf("0\n");
		else if (p == 26) printf("%d\n", a[p] * (a[p] - 1) / 2);
		else printf("%d\n", a[p] - 1);
	}
	return 0;
}