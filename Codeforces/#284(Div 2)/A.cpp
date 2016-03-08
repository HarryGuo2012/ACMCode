#include<iostream>
#include<cstring>
#include<vector>
#include<cstdio>
using namespace std;

int n,x;

int main(){
	scanf("%d%d",&n,&x);
	int u,v=0;
	int ans=0;
	while(n--){
		scanf("%d",&u);
		ans+=(u-v-1)/x;
		scanf("%d",&v);
	}
	printf("%d\n",v-ans*x);
	return 0;
}
