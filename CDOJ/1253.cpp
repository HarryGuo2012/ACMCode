#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

int n,m;

int main(){
	scanf("%d%d",&n,&m);
	int ans=m-n/2-1;
	ans=max(ans,-1);
	ans=min(ans,m);
	if(n==1)ans=-1;
	if(n==2)ans=m;
	printf("%d\n",ans);
	return 0;
}
