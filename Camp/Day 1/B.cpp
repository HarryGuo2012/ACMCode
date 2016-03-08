#include <iostream>
#include <cstring>
#include <vector>
#include <bitset>
#include <algorithm>
#include <string>
#include <queue>
#define INF 2333*2333
#define MAX_N 2333
using namespace std;

int n;
vector<int> G[MAX_N];

int d[MAX_N][MAX_N];

queue<int> que;
bool inQue[MAX_N];

void spfa(int s){
	for(int i=1;i<=n;i++)d[s][i]=INF;
	memset(inQue,0,sizeof(inQue));
	while(que.size())que.pop();
	que.push(s);
	d[s][s]=0;
	inQue[s]=1;
	while(que.size()){
		int u=que.front();
		que.pop();
		inQue[u]=0;
		for(int i=0;i<G[u].size();i++){
			int v=G[u][i];
			//cout<<d[s][u]+1<<endl;
			if(d[s][v]>d[s][u]+1){
				d[s][v]=d[s][u]+1;
				if(!inQue[v]){
					inQue[v]=1;
					que.push(v);
				}
			}
		}
	}
}

char cc;

int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			char c;
			cin>>c;
			if(c=='1')G[i].push_back(j);
		}
	for(int i=1;i<=n;i++)
		spfa(i);
	long long ans=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			if(d[i][j]==INF)
				d[i][j]=n;
			ans=ans+(long long)d[i][j]*d[i][j];
		}
	cout<<ans<<endl;
	//cin>>cc;
	return 0;
}