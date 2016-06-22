#include <cstdio>

char buff[5];

int n, m;

int main() {
    int state[2];
    state[0] = 0;
    state[1] = (1 << 30) - 1;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        int t;
        scanf("%s%d", buff, &t);
        for (int j = 0; j < 2; j++) {
            if (buff[0] == 'A') state[j] &= t;
            if (buff[0] == 'O') state[j] |= t;
            if (buff[0] == 'X') state[j] ^= t;
        }
    }
    int ans = 0;
    for (int i = 0; i <= m; i++) {
        int t = 0;
        for (int j = 0; j < 30; j++) 
            t |= (state[i >> j & 1] >> j & 1) << j;
        if (ans < t) ans = t;
    }
    printf("%d\n", ans);
    return 0;
}