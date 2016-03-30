#include<cassert>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int M = 1005;

int n, m;

int cnt, ans[M][M];

void putSquare(int x, int y, int len) {
	++cnt;
	for (int i = x; i < x + len; ++i) {
		for (int j = y; j < y + len; ++j) {
			assert(0 <= i && i < m);
			assert(0 <= j && j < m);
			assert(ans[i][j] == -1);
			ans[i][j] = cnt;
		}
	}
}

void printAns() {
	printf("%d\n", m);
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < m; ++j) {
			printf("%d%c", ans[i][j], j == m - 1 ? '\n' : ' ');
		}
	}
}

int main() {
	memset(ans, -1, sizeof(ans));
	scanf("%d", &n);
	if (n == 2 || n == 3 || n == 5) {
		puts("Impossible");
	} else {
		puts("Possible");
		if (n == 1) {
			m = 1;
			putSquare(0, 0, 1);
		} else if (n == 4) {
			m = 2;
			putSquare(0, 0, 1);
			putSquare(0, 1, 1);
			putSquare(1, 0, 1);
			putSquare(1, 1, 1);
		} else if (n == 21) {
			m = 112;
			int data[21] = {50, 35, 27, 8, 19, 
					        15, 17, 11, 6, 24, 
							29, 25, 9, 2, 7, 
							18, 16, 42, 4, 37, 33};
			for (int i = 0; i < m; ++i) {
				for (int j = 0; j < m; ++j) {
					if (ans[i][j] == -1) {
						putSquare(i, j, data[cnt]);
					}
				}
			}
		} else if (n % 2 == 0) {
			int l = n / 2, big = l - 1;
			m = l;
			for (int i = 0; i < m; ++i) {
				for (int j = 0; j < m; ++j) {
					if (ans[i][j] == -1) {
						putSquare(i, j, cnt == l ? big : 1);
					}
				}
			}
		} else {
			int l = (n - 3) / 2, big = l - 1;
			m = l * 2;
			putSquare(2, 0, big);
			putSquare(2, big, big);
			putSquare(2 + big, 0, big);
			putSquare(2 + big, big, big);	
			for (int i = 0; i < m; ++i) {
				for (int j = 0; j < m; ++j) {
					if (ans[i][j] == -1) {
						putSquare(i, j, 2);
					}
				}
			}
		}
		printAns();
	}
	return 0;
}
