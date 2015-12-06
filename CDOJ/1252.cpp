#include<iostream>
#include<cstring>
#include<vector>
#include<cstdio>
using namespace std;

typedef long long ll;
int N,M;
ll sum=0,ma=-1;

int main(){
	scanf("%d%d",&N,&M);
	for(int i=0;i<N;i++){
		int a;
		scanf("%d",&a);
		ma=max(ma,(ll)a);
		sum+=a;
	}
	printf("%lld\n",max(ma,sum/M+(sum%M!=0)));
	return 0;
}
