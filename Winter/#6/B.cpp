#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
#include<cstdio>
#include<algorithm>
#define INF 12345678
#define MAX_N 2222
using namespace std;

vector<int> G[MAX_N];
int d[MAX_N];

int n,m;

queue<int> que;
bool inQue[MAX_N];
void spfa(){
	que.push(n);
	for(int i=0;i<MAX_N;i++)
		d[i]=INF;
	d[n]=0;
	while(que.size()){
		int u=que.front();
		que.pop();
		for(int i=0;i<G[u].size();i++){
			int v=G[u][i];
			if(d[v]>d[u]+1){
				d[v]=d[u]+1;
				if(!inQue[v])que.push(v);
			}
		}
	}
}


int main(){
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	scanf("%d%d",&n,&m);
	getchar();
	for(int i=1;i<=n;i++,getchar())
		for(int j=1;j<=m;j++){
			char c;
			scanf("%c",&c);
			if(c=='#')G[i].push_back(j+n),G[j+n].push_back(i);
		}
	spfa();
	if(d[1]>=INF)
		cout<<-1<<endl;
	else
		cout<<d[1]<<endl;
	return 0;
}