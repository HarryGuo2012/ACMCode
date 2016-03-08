#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

const int maxn = 1e5+6;
const int maxm = 20;
vector<int> E[maxn];
int Xor[maxn];
int Vis[maxn];
int N;
int lca[maxn][maxm];
int deep[maxn];
void dfs(int x,int fa)
{
    Xor[x]=Xor[fa]^x;
    for(int i=0;i<E[x].size();i++)
    {
        int v=E[x][i];
        if(v==fa)continue;
        lca[v][0]=x;
        deep[v]=deep[x]+1;
        for(int j=1;j<maxm;j++)
        {
            int F = lca[v][j-1];
            if(F==0)continue;
            lca[v][j]=lca[F][j-1];
        }
        dfs(v,x);
    }
}

int up(int x,int d)
{
    for(int i=maxm-1;i>=0;i--)
    {
        if(d<(1<<i))continue;
        x=lca[x][i];
        d-=(1<<i);
    }
    return x;
}
int Lca(int x,int y)
{
    if(deep[x]>deep[y])swap(x,y);
    y=up(y,deep[y]-deep[x]);
    if(x==y)return x;
    for(int i=maxm-1;i>=0;i--)
    {
        if(lca[x][i]!=lca[y][i])
            x=lca[x][i],y=lca[y][i];
    }
    return lca[x][0];
}
int get_xor()
{
    dfs(1,0);
    int ans = 0;
    for(int i=1;i<=N;i++)
    {
        for(int j=i+1;j<=N;j++)
        {
            int p = Xor[i]^Xor[j]^Lca(i,j);
            if(p==0)ans++;
        }
    }
    return ans;
}

int main(){
	cin>>N;
	for(int i=0;i<N;i++){
		int u,v;
		cin>>u>>v;
		E[u].push_back(v);
		E[v].push_back(u);
	}
	cout<<get_xor()<<endl;
	return 0;
}