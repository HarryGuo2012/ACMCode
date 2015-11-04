#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
#include<cstdio>
#include<string>
#include<algorithm>
#define MAX_N 11234
using namespace std;

int n,m;
vector<int> G[MAX_N];

int dfn[MAX_N],low[MAX_N],ind=0;
bool vis[MAX_N];

struct node{
    public:
        int pos,val;
        void print(){
            cout<<pos-1<<" "<<val<<endl;
        }
};

bool cmp(node a,node b){
    if(a.val==b.val)return a.pos<b.pos;
    return a.val>b.val;
}

node d[MAX_N];

void Tarjan(int u,int p){
    d[u].pos=u,d[u].val=1;
    dfn[u]=low[u]=++ind;
    vis[u]=1;
    int child=0;
    for(int i=0;i<G[u].size();i++){
        int v=G[u][i];
        if(v==p)continue;
        if(!vis[v]){
            child++;
            Tarjan(v,u);
            low[u]=min(low[v],low[u]);
            if(low[v]>=dfn[u]&&p!=0)d[u].val++;
        }
        else low[u]=min(dfn[v],low[u]);
    }
    if(p==0&&child>1)d[u].val=child;
}

void init(){
    memset(vis,0,sizeof(vis));
    memset(dfn,0,sizeof(dfn));
    memset(low,0,sizeof(low));
    ind=0;
    for(int i=0;i<=n;i++)G[i].clear();
}

int main(){
    cin.sync_with_stdio(false);
    while(true){
        cin>>n>>m;
        if(n==0&&m==0)break;
        init();
        while(true){
            int u,v;
            cin>>u>>v;
            if(u==-1)break;
            u++;v++;
            G[u].push_back(v);
            G[v].push_back(u);
        }
        Tarjan(1,0);
        sort(d+1,d+1+n,cmp);
        for(int i=1;i<=m;i++)
            d[i].print();
        cout<<endl;
    }
    return 0;
}
