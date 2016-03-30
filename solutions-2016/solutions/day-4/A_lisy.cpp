#include <stdio.h>
#include <string.h>

#include <algorithm>

using namespace std;

const int N = 410;
const int M = 2 * 160010;//ע��߲�Ҫ������
const int inf = 1000000000;
struct Node{
    int f, t, c, w;
}e[M];
int next[M], point[N], dis[N], q[N], pre[N], ne;
bool u[N];
int mmin(int x, int y){return x < y ? x : y;}
void init(){
    memset(point, -1, sizeof(point));
    ne = 0;
}
void add_edge(int f, int t, int d1, int d2, int w){	//���,�յ�,��������,��������,����
    e[ne].f = f, e[ne].t = t, e[ne].c = d1, e[ne].w = w;
    next[ne] = point[f], point[f] = ne++;
    e[ne].f = t, e[ne].t = f, e[ne].c = d2, e[ne].w = -w;
    next[ne] = point[t], point[t] = ne++;
}
bool spfa(int s, int t, int n){
    int i, tmp, l, r;
    memset(pre, -1, sizeof(pre));
    for(i = 0; i < n; ++i)
        dis[i] = inf;
    dis[s] = 0;
    q[0] = s;
    l = 0, r = 1;
    u[s] = true;
    while(l != r) {
        tmp = q[l];
        l = (l + 1) % (n + 1);
        u[tmp] = false;
        for(i = point[tmp]; i != -1; i = next[i]) {
            if(e[i].c && dis[e[i].t] > dis[tmp] + e[i].w) {
                dis[e[i].t] = dis[tmp] + e[i].w;
                pre[e[i].t] = i;
                if(!u[e[i].t]) {
                    u[e[i].t] = true;
                    q[r] = e[i].t;
                    r = (r + 1) % (n + 1);
                }
            }
        }
    }
    if(pre[t] == -1) return false;
    return true;
}
void MCMF(int s, int t, int n, int &flow, int &cost){    //Դ,��,����,��¼flow��cost�ı���
    int tmp, min;
    flow = cost = 0;
    while(spfa(s, t, n)) {
        min = inf, tmp = t;
        while(tmp != s) {
            min = mmin(min, e[pre[tmp]].c);
            tmp = e[pre[tmp]].f;
        }
        tmp = t;
        while(tmp != s) {
            e[pre[tmp]].c -= min;
            e[pre[tmp] ^ 1].c += min;
            tmp = e[pre[tmp]].f;
        }
        flow += min;
        cost += min * dis[t];
    }
}
int uu[210][210];
int ud[210];
int c[210], d[210];
int main() {
    int n, m, i, j, nn;
    scanf("%d%d", &n, &m);
    init();
    memset(uu, -1, sizeof(uu));
    int ss = n + m + 1, tt = ss + 1;
    for (i = 0; i < m; i++) {
        scanf("%d", &nn);
        for (j = 0; j < nn; j++) {
            scanf("%d", &c[j]); c[j]--;
            d[c[j]]++;
        }
        c[nn] = c[0];
        add_edge(n + i, tt, 2 * nn - 4, 0, 0);
        add_edge(ss, n + i, nn, 0, 0);
        for (j = 0; j < nn; j++) {
            add_edge(c[j], n + i, 4, 0, 0);
            if (uu[c[j]][c[j + 1]] >= 0) {
                int ii = uu[c[j]][c[j + 1]];
                add_edge(n + i, n + ii, 1000, 0, 1);
                add_edge(n + ii, n + i, 1000, 0, 1);
                uu[c[j]][c[j + 1]] = uu[c[j + 1]][c[j]] = -1;
            } else {
                uu[c[j]][c[j + 1]] = uu[c[j + 1]][c[j]] = i;
            }
        }
    }
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (uu[i][j] >= 0) {
                ud[i] = ud[j] = 1;
                int ii = uu[i][j];
                add_edge(n + m, n + ii, 1000, 0, 1);
                add_edge(n + ii, n + m, 1000, 0, 1);
            }
        }
    }
    int cnt = 0;
    for (i = 0; i < n; i++) {
        if (ud[i]) {
            cnt++;
            d[i]++;
            add_edge(i, n + m, 4, 0, 0);
        }
        add_edge(ss, i, 4 - d[i], 0, 0);
    }
    add_edge(ss, n + m, cnt, 0, 0);
    add_edge(n + m, tt, cnt * 2 + 4, 0, 0);
    MCMF(ss, tt, n + m + 3, i, j);
    printf("%d\n", j);
    return 0;
}
