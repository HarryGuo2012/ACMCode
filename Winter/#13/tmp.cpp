#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <ctime>
#define MAX_N 11
using namespace std;

int n,m;
vector<int> G[MAX_N];

vector<int> cnt;

int main(){
	srand(time(0));
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		u--,v--;
		G[u].push_back(v);
		G[v].push_back(u);
	}

	for(int i=0;i<1000000;i++){
		int u=1,s=1;
		int step=0;
		while(s!=(1<<n)-1){
			int r=rand()%G[u].size();
			u=G[u][r];
			s|=(1<<u);
			step++;
		}
		cnt.push_back(step);
	}
	double sum=0;
	for(int i=0;i<cnt.size();i++)
		sum+=cnt[i];
	printf("%.6f\n",sum/cnt.size());
	cin>>n;
	return 0;
}