#include<iostream>
#include<cstring>
#include<vector>
#include<cstdio>
#include<algorithm>
#include<queue>
#define MAX_N 405
#define INF 500
using namespace std;

vector<int> rG[MAX_N];
vector<int> bG[MAX_N];

int n,m;

bool vis[MAX_N],inQue[MAX_N];
int d[MAX_N];

int spfa(vector<int> G[MAX_N]){
	queue<int> que;
	fill(d+1,d+1+n,INF);
	memset(inQue,0,sizeof(inQue));
	que.push(1);
	inQue[1]=1;
	d[1]=0;
	while(que.size()){
		int u=que.front();
		que.pop();
		for(auto v:G[u]){
			if(d[v]>d[u]+1){
				d[v]=d[u]+1;
				if(!inQue[v]){
					inQue[v]=1;
					que.push(v);
				}
			}
		}
	}
	return d[n];
}

int main(){
	cin.sync_with_stdio(false);
	cin>>n>>m;
	for(int i=0;i<m;i++){
		int u,v;
		cin>>u>>v;
		rG[u].push_back(v);
		rG[v].push_back(u);
	}
	for(int i=1;i<=n;i++){
		memset(vis,0,sizeof(vis));
		for(auto c:rG[i])vis[c]=1;
		for(int j=1;j<=n;j++)
			if(j!=i&&vis[j]==0)
				bG[j].push_back(i);
	}
	int d1=spfa(rG),d2=spfa(bG);
	if(d1==INF||d2==INF)cout<<-1<<endl;
	else cout<<max(d1,d2)<<endl;
	return 0;
}
