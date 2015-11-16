#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#include<cmath>
#define MAX_N 233333
using namespace std;

int n;
int x[MAX_N],y[MAX_N];

int w[MAX_N];

vector<int> v[MAX_N];

struct node{
	public:
		int id,x;
		node(int iid,int xx):id(iid),x(xx){}
		node(){}
};

vector<node> u[MAX_N];

bool cmp1(node a,node b){
	return a.x<b.x;
}

int mod=100000;

bool cmp(int a,int b){
	return x[a]<x[b];
}

int po[MAX_N];
int ans[MAX_N];

int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%d%d",&x[i],&y[i]);
		int t=y[i]-x[i]+mod;
		v[t].push_back(i);
	}
	for(int i=0;i<MAX_N;i++)sort(v[i].begin(),v[i].end(),cmp);
	bool flag=true;

	for(int i=0;i<n;i++){
		int w;
		scanf("%d",&w);
		if(!flag)continue;
		w+=mod;
		if(po[w]==v[w].size()){
			flag=false;
			continue;
		}
		ans[i]=v[w][po[w]];
		po[w]++;
	}

	if(!flag){
		printf("NO\n");
		return 0;
	}
	for(int i=0;i<n;i++){
		int t=ans[i];
		u[y[t]].push_back(node(i,x[t]));
	}	
	for(int i=0;i<MAX_N;i++){
		if(u[i].size()<=1)continue;
		sort(u[i].begin(),u[i].end(),cmp1);
		for(int j=0;j<u[i].size()-1;j++)
			if(u[i][j].id>u[i][j+1].id){
				printf("NO\n");
				return 0;
			}
	}
	printf("YES\n");
	for(int i=0;i<n;i++)
		printf("%d %d\n",x[ans[i]],y[ans[i]]);
	return 0;
}
