#include <cstdio>
#include <cstring>
#include <algorithm>

#define MAX_S 5

int n, m;

const int L = 30;
int state[2];

char buff[MAX_S];

int dp[L + 2][2];

void update(int &x, int a) {
    x = std::max(x, a);
}

int main() {
    memset(dp, -1, sizeof(dp));
    state[1] = (1 << L) - 1;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        int t;
        scanf("%s%d", buff, &t);
        for (int j = 0; j < 2; j++) {
            if (buff[0] == 'A') state[j] &= t;
            if (buff[0] == 'X') state[j] ^= t;
            if (buff[0] == 'O') state[j] |= t;
        }
    }
    dp[L][1] = 0;
    for (int i = L - 1; i >= 0; i--) {
        int z = state[0] >> i & 1, o = state[1] >> i & 1;
        if (m >> i & 1) {
            if (dp[i + 1][0] != -1) {
                update(dp[i][0], dp[i + 1][0] | (z << i));
                update(dp[i][0], dp[i + 1][0] | (o << i));
            }
            if (dp[i + 1][1] != -1) {
                update(dp[i][0], dp[i + 1][1] | (z << i));
                update(dp[i][1], dp[i + 1][1] | (o << i));
            }
        }
        else {
            if (dp[i + 1][0] != -1) {
                update(dp[i][0], dp[i + 1][0] | (z << i));
                update(dp[i][0], dp[i + 1][0] | (o << i));
            }
            if (dp[i + 1][1] != -1) 
                update(dp[i][1], dp[i + 1][1] | (z << i));
        }
    }
    printf("%d\n", std::max(dp[0][0], dp[0][1]));
    return 0;
}