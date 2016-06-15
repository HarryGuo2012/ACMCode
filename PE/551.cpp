#include <cstdio>

#define MAX_N (1 << 7)

bool a[MAX_N];

int H[3] = {116, 106, 89};

void output(int x) {
	for (int i = 6; i >= 0; i--)
		printf("%d", x >> i & 1);
	printf("\n");
}

int main() {
	for (int i = 0; i < MAX_N; i++) {
		int x = i;
		while (x) {
			if (x & 1) a[i] = !a[i];
			x >>= 1;
		}
	}
	for (int i = 0; i < MAX_N; i++) {
		bool flag = 0;
		for (int j = 0; j < 3; j++)
			flag |= a[H[j] & i];
		if (!flag) output(i); 
	}
	return 0;
}