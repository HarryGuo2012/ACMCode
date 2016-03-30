#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#define MAX_N 22
using namespace std;

bool vis[MAX_N];

bool check(int u,int v){
	int a=min(u,v),b=max(u,v);
	if(a==1&&b==3&&vis[2]==0)return false;
	if(a==1&&b==7&&vis[4]==0)return false;
	if(a==1&&b==9&&vis[5]==0)return false;
	if(a==2&&b==8&&vis[5]==0)return false;
	if(a==3&&b==7&&vis[5]==0)return false;
	if(a==3&&b==9&&vis[6]==0)return false;
	if(a==4&&b==6&&vis[5]==0)return false;
	if(a==7&&b==9&&vis[8]==0)return false;
	return true;
}

int T;
int n,a[MAX_N];

bool solve(){
	memset(vis,0,sizeof(vis));
	if(n<4)return false;
	for(int i=1;i<=n;i++)
		if(a[i]<=0||a[i]>9)return false;
	vis[a[1]]=1;
	for(int i=2;i<=n;i++){
		if(vis[a[i]])return false;
		if(!check(a[i-1],a[i]))return false;
		vis[a[i]]=1;
	}
	return true;
}

int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		if(solve())
			printf("valid\n");
		else
			printf("invalid\n");
	}
	return 0;
}