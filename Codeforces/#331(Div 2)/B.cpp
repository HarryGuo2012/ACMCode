#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
using namespace std;

typedef long long ll;

int n;

int main(){
	scanf("%d",&n);
	ll ans=0;
	ll now=0;
	for(int i=0;i<n;i++){
		ll b;
		scanf("%I64d",&b);
		if(now==b)continue;
		ans+=abs(now-b);
		now=b;
	}
	printf("%I64d\n",ans);
	return 0;
}
