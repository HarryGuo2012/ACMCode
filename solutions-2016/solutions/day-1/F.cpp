#include <cstdio>
#include <cstring>

const int MOD = (int)1e9 + 7;

const int N = 200000;
const int D = 16;
const int B = 1024;

int a[N], dp[N], table[1 << D];

void update(int &x, int a) {
    x += a;
    if (x >= MOD) {
        x -= MOD;
    }
}

int main() {
    int n, d;
    scanf("%d%d", &n, &d);
    memset(a, 0, sizeof(*a) * n);
    for (int i = 0; i < n; ++ i) {
        char buffer[d + 1];
        scanf("%s", buffer);
        for (int j = 0; j < d; ++ j) {
            a[i] |= buffer[j] - '0' << j;
        }
    }
    int result = 0;
    for (int i = 0; i < n; ++ i) {
        if (i % B == 0) {
            memset(table, 0, sizeof(*table) << d);
            for (int j = 0; j < i; ++ j) {
                update(table[a[j]], dp[j]);
            }
            for (int j = 0; j < d; ++ j) {
                for (int mask = (1 << d) - 1; mask >= 0; -- mask) {
                    if (mask >> j & 1) {
                        update(table[mask], table[mask ^ 1 << j]);
                    }
                }
            }
        }
        dp[i] = 1;
        update(dp[i], table[a[i]]);
        for (int j = (i / B) * B; j < i; ++ j) {
            if ((a[i] & a[j]) == a[j]) {
                update(dp[i], dp[j]);
            }
        }
        update(result, dp[i]);
    }
    printf("%d\n", result);
    return 0;
}
