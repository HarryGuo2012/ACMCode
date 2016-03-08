#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#define MAX_N 111
using namespace std;

int father[MAX_N];

int u[MAX_N],v[MAX_N];
int n;

void init(){
	for(int i=0;i<=n;i++)
		father[i]=i;
}

int Find(int x){
	if(father[x]==x)return x;
	return father[x]=Find(father[x]);
}

void unionSet(int x,int y){
	int a=Find(x),b=Find(y);
	if(a==b)return;
	father[a]=b;
}

bool Same(int x,int y){
	return Find(x)==Find(y);
}

bool work(int a,int b){
	init();
	for(int i=1;i<=n+1;i++){
		if(i==a||i==b)continue;
		unionSet(u[i],v[i]);
	}
	for(int i=1;i<=n;i++)
		if(!Same(1,i))
			return false;
	return true;
}

int T;

int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n+1;i++)
			scanf("%d%d",&u[i],&v[i]);
		int cnt=0;
		for(int i=1;i<=n+1;i++)
			cnt+=work(i,i);
		//cout<<cnt<<endl;
		for(int i=1;i<=n+1;i++)
			for(int j=1;j<i;j++)
				cnt+=work(i,j);
		printf("%d\n",cnt);
	}
	return 0;
}