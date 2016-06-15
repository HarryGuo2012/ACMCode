#include <cstdio>
#include <cmath>
#include <cstring>

#define MAXN 300005
#define DB double

const DB pi = acos(-1.0);
struct cp {
    DB x, y;
    cp(){} cp(DB a, DB b):x(a), y(b){}
    cp operator + (const cp &r) const { return cp(x+r.x, y+r.y); }
    cp operator - (const cp &r) const { return cp(x-r.x, y-r.y); }
    cp operator * (const cp &r) const { return cp(x*r.x - y*r.y, x*r.y+y*r.x); }
} a[MAXN], b[MAXN], tmp;
inline void Swap(cp &a, cp &b) { tmp=a; a=b; b=tmp; }
int n, m;
inline void fft(cp *a, int f) {
    for(int i = 0, j = 0; i < n; ++ i) {
        if(i > j) Swap(a[i], a[j]);
        for(int l = (n>>1); (j^=l) < l; l >>= 1);
    }
    for(int i = 1; i < n; i <<= 1) {
        cp wn(cos(pi/i), f*sin(pi/i));
        for(int j = 0; j < n; j += i<<1) {
            cp w(1, 0);
            for(int k = 0; k < i; ++ k, w = w * wn) {
                cp x = a[j + k], y = w * a[j + k + i];
                a[j + k] = x + y;
                a[j + k + i] = x - y;
            }
        }
    }
    if(-1 == f) for(int i = 0; i < n; ++ i) a[i].x /= n;
}
void convolution(int A[], int B[], int &nA, int nB){
    n = nA, m = nB;
    //scanf("%d%d", &n, &m);
    for(int i = 0; i <= n; ++ i) a[i].x = A[i];
    for(int i = 0; i <= m; ++ i) b[i].x = B[i];
    for(m = n+m, n = 1; n <= m; n <<= 1);
    fft(a, 1); fft(b, 1);
    for(int i = 0; i <= n; ++ i) a[i] = a[i] * b[i];
    fft(a, -1);
    for(int i = 0; i <= m; ++ i) A[i] = (int)(a[i].x + 0.1);
    nA = m;
}

void init(){
    for(int i = 0; i < MAXN; i++)
        a[i].x = a[i].y = 0.0;
    for(int i = 0; i < MAXN; i++)
        b[i].x = b[i].y = 0.0;
}

int n1, n2, n5;
int A[MAXN], B[MAXN];

int main(){
    while(scanf("%d%d%d", &n1, &n2, &n5) == 3){
        if(n1 + n2 + n5 == 0)
            break;
        init();
        memset(A, 0, sizeof(A));
        memset(B, 0, sizeof(B));
        for(int i = 0; i <= n1; i++)
            A[i] = 1;
        for(int i = 0; i <= n2; i++)
            B[2 * i] = 1;
        n1++;
        convolution(A, B, n1, 2 * n2 + 1);
        memset(B, 0, sizeof(B));
        for(int i = 0; i <= n5; i++)
            B[5 * i] = 1;
        n1++;
        init();
        convolution(A, B, n1, 5 * n5 + 1);
        int pos = 0;
        while(A[pos]) pos++;
        printf("%d\n", pos);
    }
    return 0;
}