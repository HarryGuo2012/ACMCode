#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

long long ans=0;

void gcd(int a,int b){
	int ma=max(a,b);
	int mi=min(a,b);
	ans+=ma/mi;
	if(ma%mi!=0)
		gcd(mi,(ma%mi));
}

int T;
int n,m;
int main(){
	scanf("%d",&T);
	while(T--){
		ans=0;
		scanf("%d%d",&n,&m);
		gcd(n,m);
		printf("%lld\n",ans);
	}
	return 0;
}