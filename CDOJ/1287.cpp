#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>
#define MAX_N 2222

std::queue<int> que;
std::vector<int> G[MAX_N];
int distance[MAX_N];
bool vis[MAX_N];
int n;

long long bfs(int s){
	while(que.size())que.pop();
	for(int i=0;i<n;i++)
		distance[i]=n;
	memset(vis,0,sizeof(vis));
	distance[s]=0;vis[s]=1;
	que.push(s);
	while(que.size()){
		int u=que.front();que.pop();
		for(auto v:G[u]){
			if(vis[v])continue;
			distance[v]=distance[u]+1;
			vis[v]=1;
			que.push(v);
		}
	}
	long long res=0;
	for(int i=0;i<n;i++)
		res=(long long)distance[i]*distance[i];
	return res;
}

char buff[MAX_N][MAX_N];

int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%s",buff[i]);
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			if(buff[i][j]=='1')
				G[i].push_back(j);
	long long ans=0;
	for(int i=0;i<n;i++)
		ans+=bfs(i);
	std::cout<<ans<<std::endl;
	return 0;
}