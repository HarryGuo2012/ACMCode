#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cstdlib>
#include<set>
#include<climits>
#include<ctime>
#include<stack>
#include<cstdio>
#define MAX_N 50004
#define MAX_A 1550006
using namespace std;

int a[MAX_N];

const static int TreapSize = MAX_A;
struct node{
    node * ch[2];
    int key , v , s , cnt ;
    int cmp(int x) const{
        if(key==x) return -1;
        return x < key ? 0 : 1;
    }
};

node nt[TreapSize];
int Q[TreapSize] , sz ;

//必须调用 init() 函数在初始化的时候,可调用的静态内存在Q数组中,是一个栈
void init(){
    srand(time(NULL));
    for(int i = 0 ; i < TreapSize ; ++ i) Q[i] = i;sz = TreapSize;
}

struct Treap
{
    node * root;
    int treapsz;

    void init(){
        root=0;treapsz=0;
    }

    void push_up(node * o){
        o->s=o->cnt;
        if(o->ch[0]) o->s+=o->ch[0]->s;
        if(o->ch[1]) o->s+=o->ch[1]->s;
    }

    void init_node(node * x,int key){
        x->ch[0]=x->ch[1]=0;x->s=x->cnt=1;
        x->key=key,x->v=rand();
    }

    inline int Get_idx(node * f){
        return f-nt;
    }
    // d = 0 , Left - rotate ; d = 1 , right - rotate
    inline void rotate(node * & o , int d){
        node * f = o->ch[d^1];
        o->ch[d^1] = f->ch[d] , f->ch[d] = o;
        push_up(o) ; push_up(f);
        o = f;
    }

    void process_insert(node *& u , int x){
        if(!u){
            init_node(nt + Q[--sz] , x );
            u = nt + Q[sz];
        }
        else if(u->key == x){
            u->cnt ++ ;
        }
        else{
            int d = x < u->key ? 0 : 1;
            process_insert(u->ch[d],x);
            if(u->ch[d]->v > u->v) rotate( u , d ^ 1 );
        }
        push_up(u);
    }

    void process_remove(node *&u ,int x){
        if(!u){
            treapsz++;
            return;
        }
        int d = u->cmp(x);
        if(d==-1){
            if (u->ch[0] && u->ch[1]){
                int d = u->ch[0]->v > u->ch[1]->v ? 1 : 0;
                rotate( u , d );
                process_remove( u -> ch[d] , x);
            }
            else{
                int d2;
                if(!u->ch[0]) d2 = 1;
                else d2 = 0;
                u->cnt--;
                if(!u->cnt){
                    Q[sz++] = Get_idx(u);
                    u = u->ch[d2];
                }
            }
        }
        else process_remove( u->ch[d] , x );
        if(u) push_up(u);
    }

    // 带入参数 find (trep.root , x )
    // 在treap中查找元素 x , 查找成功返回true , 失败返回false
    bool find(node * o ,int x){
        while(o){
            int d = o->cmp(x);
            if(d==-1) return true;
            o=o->ch[d];
        }
        return false;
    }

    //插入某个元素 x
    void insert(int x){
        process_insert(root,x);
        treapsz++;
    }

    //删除某个元素 x ,若 x 不存在无影响
    void remove(int x){
        process_remove(root,x);
        treapsz--;
    }

    //返回 treap 目前的节点数目
    int size(){
        return treapsz;
    }

    //找第 k 大的元素，未找到则返回-1
    int kth(int k){
        node * u = root;
        while(u && u->s>=k && k >= 1){
            int s = u->ch[1] ? u->ch[1]->s : 0;
            if(k>=s+1&&k<=s+u->cnt) return u->key;
            else if(k<=s) u = u -> ch[1];
            else{
                k -= (s + u->cnt);
                u=u->ch[0];
            }
        }
        return -1;
    }

    //计算严格小于 x 的数的数量
    int count_less(int x){
        node * o = root;
        int s = 0;
        while(o){
            int d = o->cmp(x);
            if(d==1) s += o->ch[0]?o->ch[0]->s+o->cnt:o->cnt;
            else if(d==-1) s += o->ch[0]?o->ch[0]->s:0;
            if(d==-1) break;
            o=o->ch[d];
        }
        return s;
    }

    //获取某个数的 rank
    //某个数的rank定义为 严格小于这个数的数目 + 1
    int rank(int x){
        return count_less(x) + 1;
    }
};

int N,M;

struct SegmentTree {
#define lchild L,m,v<<1
#define rchild m+1,R,v<<1|1

    struct Node {
        Treap tr;

        Node() {
            tr.init();
        }

    } tree[MAX_N*4];

    SegmentTree() { }

    void build(int L = 1, int R = N, int v = 1) {
        tree[v] = Node();
        for (int i = L; i <= R; i++)
            tree[v].tr.insert(a[i]);
        if (L == R)return;
        int m = (L + R) >> 1;
        build(lchild);
        build(rchild);
    }

    void update(int i, int x, int L = 1, int R = N, int v = 1) {
        tree[v].tr.remove(a[i]);
        tree[v].tr.insert(x);
        if(L==R)return;
        int m = (L + R) >> 1;
        if (i <= m)update(i, x, lchild);
        if (i > m)update(i, x, rchild);
    }

    //change a[i] to x
    int query(int a, int b, int x, int L = 1, int R = N, int v = 1) {
        if (a <= L && R <= b)return tree[v].tr.count_less(x);
        int res = 0;
        int m = (L + R) >> 1;
        if (a <= m)res += query(a, b, x, lchild);
        if (b > m)res += query(a, b, x, rchild);
        return res;
    }
}seg;


set<int> se[MAX_A];
int num[MAX_N];

int getA(int i,int x){
    if(se[x].empty())return 0;
    set<int>::iterator it=se[x].lower_bound(i);
    if(it==se[x].begin())return 0;
    it--;
    return *it;
}

int main() {
    init();
    //freopen("data.txt","r",stdin);
    //freopen("WA.txt","w",stdout);
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= N; i++) {
        int t;
        scanf("%d", &t);
        num[i] = t;
        se[t].insert(i);
    }
    for (int i = 1; i <= N; i++)
        a[i] = getA(i, num[i]);
    /*
    for(int i=1;i<=N;i++)
        cout<<a[i]<<" ";
    cout<<endl;
     */
    seg.build();
    while (M--) {
        char op[2];
        int x, y;
        scanf("%s %d%d", op, &x, &y);
        if (op[0] == 'M') {
            x++;
            if(y==num[x])continue;
            seg.update(x, getA(x, y));
            set<int>::iterator it = se[y].lower_bound(x+1);
            if (it != se[y].end()){
                seg.update(*it, x);
                a[*it] = x;
            }
            it=se[num[x]].lower_bound(x+1);
            if(it!=se[num[x]].end()){
                seg.update(*it,getA(x,num[x]));
                a[*it]=getA(x,num[x]);
            }
            a[x] = getA(x, y);
            se[num[x]].erase(x);
            num[x] = y;
            se[y].insert(x);
            /*
            for(int i=1;i<=N;i++)
                cout<<num[i]<<" ";
            cout<<endl;
            for(int i=1;i<=N;i++)
                cout<<a[i]<<" ";
            cout<<endl;
             */
        }
        else
            printf("%d\n", seg.query(x + 1, y, x + 1));
    }
    return 0;
}

