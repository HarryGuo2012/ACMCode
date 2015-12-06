#include<iostream>
#include<cstring>
#include<vector>
#include<cstdio>
#include<queue>
#include<cstdio>
#include<algorithm>
#include<climits>
#define MAX_N 100005
#define MAX_S 24
using namespace std;

namespace fastIO{
#define BUF_SIZE 100000
#define OUT_SIZE 100000
#define ll long long
    //fread->read
    bool IOerror=0;
    inline char nc(){
        static char buf[BUF_SIZE],*p1=buf+BUF_SIZE,*pend=buf+BUF_SIZE;
        if (p1==pend){
            p1=buf; pend=buf+fread(buf,1,BUF_SIZE,stdin);
            if (pend==p1){IOerror=1;return -1;}
            //{printf("IO error!\n");system("pause");for (;;);exit(0);}
        }
        return *p1++;
    }
    inline bool blank(char ch){return ch==' '||ch=='\n'||ch=='\r'||ch=='\t';}
    inline void read(int &x){
        bool sign=0; char ch=nc(); x=0;
        for (;blank(ch);ch=nc());
        if (IOerror)return;
        if (ch=='-')sign=1,ch=nc();
        for (;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0';
        if (sign)x=-x;
    }
    inline void read(ll &x){
        bool sign=0; char ch=nc(); x=0;
        for (;blank(ch);ch=nc());
        if (IOerror)return;
        if (ch=='-')sign=1,ch=nc();
        for (;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0';
        if (sign)x=-x;
    }
    inline void read(double &x){
        bool sign=0; char ch=nc(); x=0;
        for (;blank(ch);ch=nc());
        if (IOerror)return;
        if (ch=='-')sign=1,ch=nc();
        for (;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0';
        if (ch=='.'){
            double tmp=1; ch=nc();
            for (;ch>='0'&&ch<='9';ch=nc())tmp/=10.0,x+=tmp*(ch-'0');
        }
        if (sign)x=-x;
    }
    inline void read(char *s){
        char ch=nc();
        for (;blank(ch);ch=nc());
        if (IOerror)return;
        for (;!blank(ch)&&!IOerror;ch=nc())*s++=ch;
        *s=0;
    }
    inline void read(char &c){
        for (c=nc();blank(c);c=nc());
        if (IOerror){c=-1;return;}
    }
    //getchar->read
    inline void read1(int &x){
        char ch;int bo=0;x=0;
        for (ch=getchar();ch<'0'||ch>'9';ch=getchar())if (ch=='-')bo=1;
        for (;ch>='0'&&ch<='9';x=x*10+ch-'0',ch=getchar());
        if (bo)x=-x;
    }
    inline void read1(ll &x){
        char ch;int bo=0;x=0;
        for (ch=getchar();ch<'0'||ch>'9';ch=getchar())if (ch=='-')bo=1;
        for (;ch>='0'&&ch<='9';x=x*10+ch-'0',ch=getchar());
        if (bo)x=-x;
    }
    inline void read1(double &x){
        char ch;int bo=0;x=0;
        for (ch=getchar();ch<'0'||ch>'9';ch=getchar())if (ch=='-')bo=1;
        for (;ch>='0'&&ch<='9';x=x*10+ch-'0',ch=getchar());
        if (ch=='.'){
            double tmp=1;
            for (ch=getchar();ch>='0'&&ch<='9';tmp/=10.0,x+=tmp*(ch-'0'),ch=getchar());
        }
        if (bo)x=-x;
    }
    inline void read1(char *s){
        char ch=getchar();
        for (;blank(ch);ch=getchar());
        for (;!blank(ch);ch=getchar())*s++=ch;
        *s=0;
    }
    inline void read1(char &c){for (c=getchar();blank(c);c=getchar());}
    //scanf->read
    inline void read2(int &x){scanf("%d",&x);}
    inline void read2(ll &x){
#ifdef _WIN32
        scanf("%I64d",&x);
#else
        #ifdef __linux
            scanf("%lld",&x);
        #else
            puts("error:can't recognize the system!");
        #endif
#endif
    }
    inline void read2(double &x){scanf("%lf",&x);}
    inline void read2(char *s){scanf("%s",s);}
    inline void read2(char &c){scanf(" %c",&c);}
    inline void readln2(char *s){gets(s);}
    //fwrite->write
    struct Ostream_fwrite{
        char *buf,*p1,*pend;
        Ostream_fwrite(){buf=new char[BUF_SIZE];p1=buf;pend=buf+BUF_SIZE;}
        void out(char ch){
            if (p1==pend){
                fwrite(buf,1,BUF_SIZE,stdout);p1=buf;
            }
            *p1++=ch;
        }
        void print(int x){
            static char s[15],*s1;s1=s;
            if (!x)*s1++='0';if (x<0)out('-'),x=-x;
            while(x)*s1++=x%10+'0',x/=10;
            while(s1--!=s)out(*s1);
        }
        void println(int x){
            static char s[15],*s1;s1=s;
            if (!x)*s1++='0';if (x<0)out('-'),x=-x;
            while(x)*s1++=x%10+'0',x/=10;
            while(s1--!=s)out(*s1); out('\n');
        }
        void print(ll x){
            static char s[25],*s1;s1=s;
            if (!x)*s1++='0';if (x<0)out('-'),x=-x;
            while(x)*s1++=x%10+'0',x/=10;
            while(s1--!=s)out(*s1);
        }
        void println(ll x){
            static char s[25],*s1;s1=s;
            if (!x)*s1++='0';if (x<0)out('-'),x=-x;
            while(x)*s1++=x%10+'0',x/=10;
            while(s1--!=s)out(*s1); out('\n');
        }
        void print(double x,int y){
            static ll mul[]={1,10,100,1000,10000,100000,1000000,10000000,100000000,
                             1000000000,10000000000LL,100000000000LL,1000000000000LL,10000000000000LL,
                             100000000000000LL,1000000000000000LL,10000000000000000LL,100000000000000000LL};
            if (x<-1e-12)out('-'),x=-x;x*=mul[y];
            ll x1=(ll)floor(x); if (x-floor(x)>=0.5)++x1;
            ll x2=x1/mul[y],x3=x1-x2*mul[y]; print(x2);
            if (y>0){out('.'); for (size_t i=1;i<y&&x3*mul[i]<mul[y];out('0'),++i); print(x3);}
        }
        void println(double x,int y){print(x,y);out('\n');}
        void print(char *s){while (*s)out(*s++);}
        void println(char *s){while (*s)out(*s++);out('\n');}
        void flush(){if (p1!=buf){fwrite(buf,1,p1-buf,stdout);p1=buf;}}
        ~Ostream_fwrite(){flush();}
    }Ostream;
    inline void print(int x){Ostream.print(x);}
    inline void println(int x){Ostream.println(x);}
    inline void print(char x){Ostream.out(x);}
    inline void println(char x){Ostream.out(x);Ostream.out('\n');}
    inline void print(ll x){Ostream.print(x);}
    inline void println(ll x){Ostream.println(x);}
    inline void print(double x,int y){Ostream.print(x,y);}
    inline void println(double x,int y){Ostream.println(x,y);}
    inline void print(char *s){Ostream.print(s);}
    inline void println(char *s){Ostream.println(s);}
    inline void println(){Ostream.out('\n');}
    inline void flush(){Ostream.flush();}
    //puts->write
    char Out[OUT_SIZE],*o=Out;
    inline void print1(int x){
        static char buf[15];
        char *p1=buf;if (!x)*p1++='0';if (x<0)*o++='-',x=-x;
        while(x)*p1++=x%10+'0',x/=10;
        while(p1--!=buf)*o++=*p1;
    }
    inline void println1(int x){print1(x);*o++='\n';}
    inline void print1(ll x){
        static char buf[25];
        char *p1=buf;if (!x)*p1++='0';if (x<0)*o++='-',x=-x;
        while(x)*p1++=x%10+'0',x/=10;
        while(p1--!=buf)*o++=*p1;
    }
    inline void println1(ll x){print1(x);*o++='\n';}
    inline void print1(char c){*o++=c;}
    inline void println1(char c){*o++=c;*o++='\n';}
    inline void print1(char *s){while (*s)*o++=*s++;}
    inline void println1(char *s){print1(s);*o++='\n';}
    inline void println1(){*o++='\n';}
    inline void flush1(){if (o!=Out){if (*(o-1)=='\n')*--o=0;puts(Out);}}
    struct puts_write{
        ~puts_write(){flush1();}
    }_puts;
    inline void print2(int x){printf("%d",x);}
    inline void println2(int x){printf("%d\n",x);}
    inline void print2(char x){printf("%c",x);}
    inline void println2(char x){printf("%c\n",x);}
    inline void print2(ll x){
#ifdef _WIN32
        printf("%I64d",x);
#else
        #ifdef __linux
            printf("%lld",x);
        #else
            puts("error:can't recognize the system!");
        #endif
#endif
    }
    inline void println2(ll x){print2(x);printf("\n");}
    inline void println2(){printf("\n");}
#undef ll
#undef OUT_SIZE
#undef BUF_SIZE
};
//////////////////////////////////////

struct BitTree {
public:
    vector<int> v;

    BitTree(int size) {
        //cout<<size<<endl;
        v.clear();
        v.resize(size + 3);
		for(int i=0;i<v.size();i++)v[i]=0;
    }

    BitTree() { v.resize(0); }

    int sum(int i) {
        if (i >= (int)v.size())i = v.size() - 1;
        if(i<0)return 0;
        int res = 0;
        while (i) {
            res += v[i];
            i -= i & (-i);
        }
        return res;
    }

    void update(int i, int x) {
        while (i < (int)v.size()) {
            v[i] += x;
            i += i & (-i);
        }
    }
};

struct Node {
public:
    int father,size,psize;
    BitTree bitTree;
    BitTree bitTree1;

    Node(int f, int s,int ps) : size(s),psize(ps),father(f), bitTree(s), bitTree1(ps) { 
	}

    Node() { }
};

vector<int> G[MAX_N];
int N;
int weight[MAX_N];
int ancestor[MAX_N][MAX_S];
int dis[MAX_N];

struct LCA {
public:
    LCA() {
        memset(ancestor, 0, sizeof(ancestor));
        memset(dis, 0, sizeof(dis));
    }

    void dfs(int u, int p) {
        dis[u] = dis[p] + 1;
        ancestor[u][0] = p;
        for (int i = 0; i < G[u].size(); i++) {
            int v = G[u][i];
            if (v == p)continue;
            dfs(v, u);
        }
    }

    void getAncestor() {
        dfs(1, 0);
        for (int j = 1; j < MAX_S; j++)
            for (int i = 1; i <= N; i++)
                ancestor[i][j] = ancestor[ancestor[i][j - 1]][j - 1];
    }

    int getLca(int u, int v) {
        if (dis[u] < dis[v])swap(u, v);
        for (int i = MAX_S - 1; i >= 0; i--) {
            if (dis[ancestor[u][i]] >= dis[v]) {
                u = ancestor[u][i];
                if (dis[u] == dis[v])break;
            }
        }
        if (u == v)return u;
        for (int i = MAX_S - 1; i >= 0; i--) {
            if (ancestor[u][i] != ancestor[v][i]) {
                u = ancestor[u][i];
                v = ancestor[v][i];
            }
        }
        return ancestor[u][0];
    }

    int getDis(int u, int v) {
        if(u==0)return dis[v];
        if(v==0)return dis[u];
        int l = getLca(u, v);
        return dis[u] + dis[v] - 2 * dis[l];
    }
};

bool vis[MAX_N];
int siz[MAX_N];
Node node[MAX_N];

struct CentroidTree {
public:
    LCA lca;

    CentroidTree() {
        memset(vis, 0, sizeof(vis));
        memset(siz, 0, sizeof(siz));
        lca = LCA();
    }

    void getSubtreeSize(int u, int p) {
        siz[u] = 1;
        for (int i = 0; i < G[u].size(); i++) {
            int v = G[u][i];
            if (vis[v] || v == p)continue;
            getSubtreeSize(v, u);
            siz[u] += siz[v];
        }
    }

    void searchCentroid(int u, int p, int totSize, int &centroid, int &minMaxSub) {
        int maxSub = -1;
        for (int i = 0; i < G[u].size(); i++) {
            int v = G[u][i];
            if (v == p || vis[v])continue;
            maxSub = max(siz[v], maxSub);
        }
        maxSub = max(totSize - siz[u], maxSub);
        if (maxSub < minMaxSub)centroid = u, minMaxSub = maxSub;
        for (int i = 0; i < G[u].size(); i++) {
            int v = G[u][i];
            if (v == p || vis[v])continue;
            searchCentroid(v, u, totSize, centroid, minMaxSub);
        }
    }

    void buildTree(int u, int p,int ps) {
        getSubtreeSize(u, 0);
        int nowCentroid = u, minMaxSub = INT_MAX;
        searchCentroid(u, 0, siz[u], nowCentroid, minMaxSub);
        vis[nowCentroid] = 1;
        node[nowCentroid] = Node(p, siz[u], ps);
		//if(ps<siz[u])cout<<"fuck"<<endl;
		int tmp=siz[u];
        for (int i = 0; i < G[nowCentroid].size(); i++) {
            int v = G[nowCentroid][i];
            if (vis[v])continue;
            buildTree(v, nowCentroid,tmp);
        }
    }

    void Update(int u, int x) {
        int v = u;
        while (v) {
            int d = lca.getDis(u, v),d1=lca.getDis(node[v].father,u);
            node[v].bitTree.update(d+1, x);
            if(node[v].father)
                node[v].bitTree1.update(d1+1,x);
            v = node[v].father;
        }
    }

    int Query(int u, int d) {
        int v = u, res = 0;
        while (v) {
            int di=lca.getDis(u,v),di1=lca.getDis(u,node[v].father);
            res += node[v].bitTree.sum(d-di+1);
            if(node[v].father)
                res -= node[v].bitTree1.sum(d-di1+1);
            v = node[v].father;
        }
        return res;
    }
}CT;

int Q;

int main() {
	//freopen("data.in","r",stdin);
	//freopen("WA.out","w",stdout);
    while (scanf("%d%d",&N,&Q)==2) {
        for (int i = 1; i <= N; i++)
            fastIO::read1(weight[i]);
        for (int i = 1; i <= N; i++)G[i].clear();
        for (int i = 1; i <= N - 1; i++) {
            int u, v;
            fastIO::read1(u);
            fastIO::read1(v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        CT = CentroidTree();
        CT.buildTree(1, 0,0);
        CT.lca.getAncestor();
        for (int i = 1; i <= N; i++)CT.Update(i, weight[i]);
        while (Q--) {
            char op[2];
            int x, y;
            fastIO::read1(op);
            fastIO::read1(x);
            fastIO::read1(y);
            //scanf("%s %d%d", op, &x, &y);
            if (op[0] == '!') {
                CT.Update(x, y - weight[x]);
                weight[x] = y;
            }
            else
                printf("%d\n",CT.Query(x,y));
        }
    }
    return 0;
}


