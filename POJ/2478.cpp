#include<iostream>
#include<cstring>
#include<queue>
#include<vector>
#include<cstdio>
#include<algorithm>
#define MAX_N 1000006
using namespace std;

int phi[MAX_N];

int minDiv[MAX_N],sum[MAX_N];

void getPhi(){
	for(int i=1;i<MAX_N;i++)minDiv[i]=i;
	for(int i=2;i*i<MAX_N;i++)
		if(minDiv[i]==i)
			for(int j=i*i;j<MAX_N;j+=i)
				minDiv[j]=i;
	phi[1]=1;
	for(int i=2;i<MAX_N;i++){
		phi[i]=phi[i/minDiv[i]];
		if((i/minDiv[i])%minDiv[i]==0)
			phi[i]*=minDiv[i];
		else
			phi[i]*=minDiv[i]-1;
	}
}
long long F[MAX_N];

int main(){
	getPhi();
	F[2]=phi[2];
	for(int i=3;i<MAX_N;i++)
		F[i]=F[i-1]+phi[i];
	int n;
	while(scanf("%d",&n)==1){
		if(!n)break;
		printf("%I64d\n",F[n]);
	}
	return 0;
}
