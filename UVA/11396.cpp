#include<iostream>
#include<cstring>
#include<vector>
#include<cstdio>
#include<algorithm>
#define MAX_N 555
using namespace std;

vector<int> G[MAX_N];
int n;
int d[MAX_N];

bool dfs(int u,int p){
    d[u]=d[p]^1;
    bool tmp=true;
    for(int i=0;i<G[u].size();i++){
        if(d[G[u][i]]==d[u])return false;
        if(d[G[u][i]]==-1)
            tmp&=dfs(G[u][i],u);
    }
    return tmp;
}

int main(){
    while(scanf("%d",&n)){
        if(n==0)break;
        int u,v;
        for(int i=0;i<=n;i++)G[i].clear();
        while(true){
            scanf("%d%d",&u,&v);
            if(u+v==0)break;
            G[u].push_back(v);
            G[v].push_back(u);
        }    
        bool flag=true;
        memset(d,-1,sizeof(d));
        d[0]=0;
        flag=dfs(1,0);
        memset(d,-1,sizeof(d));
        d[0]=1;
        flag&=dfs(1,0);
        if(flag)
            printf("YES\n");
        else 
            printf("NO\n");
    }
    return 0;
}
