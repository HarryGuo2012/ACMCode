#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<vector>
#define MAX_N 100005
using namespace std;

typedef long long ll;

int prime[MAX_N],tot=0;
bool check[MAX_N];
int mu[MAX_N];

void Euler(){
	memset(check,0,sizeof(check));
	mu[1]=1;
	for(int i=2;i<MAX_N;i++){
		if(!check[i]){
			prime[tot++]=i;
			mu[i]=-1;
		}
		for(int j=0;j<tot;j++){
			if(i*prime[j]>=MAX_N)break;
			check[i*prime[j]]=true;
			if(i%prime[j]==0){
				mu[i*prime[j]]=0;
				break;
			}
			else{
				mu[i*prime[j]]=-mu[i];
			}
		}
	}
}

int a,b,c,d,k;

int main(){
	Euler();
	int T;
	scanf("%d",&T);
	int cas=0;
	while(T--){
		scanf("%d%d%d%d%d",&a,&b,&c,&d,&k);
		if(k==0||k>b||k>d){
			printf("Case %d: %d\n",++cas,0);
			continue;
		}
		int n=b/k,m=d/k;
		ll res=0;
		for(int i=1;i<=min(n,m);i++)
			res+=(ll)mu[i]*(n/i)*(m/i);
		int AA=min(n,m);
		ll tmp=0;
		for(int i=1;i<=AA;i++)
			tmp+=(ll)mu[i]*(AA/i)*(AA/i);
		res-=(tmp-1)/2;
		printf("Case %d: %I64d\n",++cas,res);
	}
	return 0;
}
