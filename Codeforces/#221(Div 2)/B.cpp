#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdio>
#define MAX_N 123
using namespace std;

int income[MAX_N];

int n,m;

int main(){
	scanf("%d%d",&n,&m);
	while(m--){
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		income[a]+=c;
		income[b]-=c;
	}
	int x=0;
	for(int i=1;i<=n;i++){
		if(income[i]>0)x+=income[i];
	}
	printf("%d\n",x);
	return 0;
}
