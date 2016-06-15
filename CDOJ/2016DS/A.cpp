#include <cstdio>
#include <algorithm>

#define MAX_N 100005

int N, Q;

struct SegmentTree{
    #define lchild l, mid, v << 1
    #define rchild mid + 1, r, v << 1 | 1
    struct node{
        long long maxNum;
    }tree[MAX_N * 4];

    void pushUp(int v){
        tree[v].maxNum = std::max(tree[v << 1].maxNum, tree[v << 1 | 1].maxNum);
    }

    void update(int p, long long x, int l = 1, int r = N, int v = 1){
        if(l == r){
            tree[v].maxNum += x;
            return;
        }
        int mid = (l + r) >> 1;
        if(p <= mid) update(p, x, lchild);
        else update(p, x, rchild);
        pushUp(v);
    }

    long long query(int L, int R, int l = 1, int r = N, int v = 1){
        if(L <= l && r <= R) return tree[v].maxNum;
        long long res = 0;
        int mid = (l + r) >> 1;
        if(L <= mid) res = std::max(res, query(L, R, lchild));
        if(R > mid) res = std::max(res, query(L, R, rchild));
        return res;
    }
}seg;

int M;

int main(){
    scanf("%d%d", &N, &M);
    while(M--){
        int t, L, R;
        scanf("%d%d%d", &t, &L, &R);
        if(t == 1)
            seg.update(L, R);
        else
            printf("%lld\n", seg.query(L, R));
    }
    return 0;
}