#include <cstdio>
#include <algorithm>

#define MAX_N 5000 * 5000

int v[3000 * 5000], tot = 0;
bool vis[MAX_N];

int a, b, n, k;

int main(){
    scanf("%d%d", &a, &b);
    int g = std::__gcd(a, b);
    a /= g, b /= g;
    v[tot++] = 0;
    for(int i = 0; i < 5000; i++)
        for(int j = 0; j < 5000; j++){
            if(i == 0 && j == 0)
                continue;
            int t = i * a + j * b;
            if(t >= a * b - a - b + 5)
                break;
            vis[t] = 1;
        }

    for(int i = 0; i < MAX_N; i++)
        if(vis[i] == 1)
            v[tot++] = i;

    scanf("%d", &n);
    while(n--){
        scanf("%d", &k);
        if(k < tot)
            printf("%lld\n", (long long)v[k] * (long long)g);
        else
            printf("%lld\n", (((long long)a - 1) * (b - 1) / 2 + k) * (long long)g);
    }
    return 0;
}