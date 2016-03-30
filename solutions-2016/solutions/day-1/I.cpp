#include <algorithm>
#include <cstdio>
#include <cstring>

const int D = 15;
const int N = D << 1;
const int MOD = (int)1e9 + 7;

int graph[N][N][1 << D], result[1 << D];

void update(int &x, int a) {
    x += a;
    if (x >= MOD) {
        x -= MOD;
    }
}

void multiply(int *a, int *b, int *c, int i) {
    for (int subset = (1 << i) - 1; subset >= 0; -- subset) {
        if (a[subset]) {
            int rest = (1 << i) - 1 ^ subset;
            for (int subset2 = rest;; subset2 = subset2 - 1 & rest) {
                update(c[subset ^ subset2 ^ 1 << i], (long long)a[subset] * b[subset2] % MOD);
                if (!subset2) {
                    break;
                }
            }
        }
    }
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    memset(graph, 0, sizeof(graph));
    for (int i = 0; i < m; ++ i) {
        int a, b;
        scanf("%d%d", &a, &b);
        a --;
        b --;
        if (a > b) {
            std::swap(a, b);
        }
        graph[a][b][0] ++;
    }
    if (n & 1) {
        puts("0");
        return 0;
    }
    memset(result, 0, sizeof(result));
    result[0] = 1;
    for (int i = 0; i < n >> 1; ++ i) {
        int x = n - (i + 1 << 1);
        int y = x + 1;
        multiply(result, graph[x][y], result, i);
        for (int j = 0; j < x; ++ j) {
            for (int k = j + 1; k < x; ++ k) {
                multiply(graph[j][x], graph[k][y], graph[j][k], i);
                multiply(graph[j][y], graph[k][x], graph[j][k], i);
            }
        }
    }
    printf("%d\n", result[(1 << (n >> 1)) - 1]);
    return 0;
}
