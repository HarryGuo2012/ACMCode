#include<iostream>
#include<climits>
#include<cstring>
#include<queue>
#include<cstdio>
#include<vector>
#include<algorithm>
#define MAX_N 1000006
#define MAX_A 100005
using namespace std;

int phi[MAX_N];
int T;

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

int minPhi[MAX_N];

int main(){
	getPhi();
	fill(minPhi,minPhi+MAX_N,INT_MAX);
	phi[1]=0;
	for(int i=1;i<MAX_N;i++)minPhi[phi[i]]=min(minPhi[phi[i]],i);
	for(int i=MAX_N-2;i>=1;i--)minPhi[i]=min(minPhi[i],minPhi[i+1]);
	int T;
	scanf("%d",&T);
	int cas=0;
	while(T--){
		int n;
		scanf("%d",&n);
		long long ans=0;
		while(n--){
			int a;
			scanf("%d",&a);
			ans=ans+minPhi[a];
		}
		printf("Case %d: %lld Xukha\n",++cas,ans);
	}
	return 0;
}
