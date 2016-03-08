#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <cstdio>
#define MAX_N 5000006
using namespace std;

typedef unsigned long long ll;

ll prime[MAX_N],tot;
ll phi[MAX_N];
bool check[MAX_N];

ll f[MAX_N],sum[MAX_N];

ll mp[MAX_N],mpp[MAX_N],tim[MAX_N];

ll Pow(ll a,int x){
	ll res=1;
	while(x){
		if(x&1)res*=a;
		a*=a;
		x>>=1;
	}
	return res;
}

ll getPowSum(ll p,int t){
	return p*(Pow(p,t)-1)/(p-1);
}

void Euler(){
	phi[1]=1;
	for(int i=2;i<MAX_N;i++){
		if(!check[i]){
			phi[i]=i-1;
			prime[tot++]=i;
			mp[i]=mpp[i]=i;
			tim[i]=1;
		}
		if(i==mpp[i]){
			ll p=mp[i];
			f[i]=getPowSum(p*p,tim[i])-getPowSum(p*p,tim[i])/p;
		}
		else
			f[i]=f[mpp[i]]*f[i/mpp[i]];
		for(int j=0;j<tot;j++){
			if(i*prime[j]>=MAX_N)break;
			check[i*prime[j]]=1;
			mp[i*prime[j]]=prime[j];
			if(i%prime[j]==0){
				mpp[i*prime[j]]=mpp[i]*prime[j];
				tim[i*prime[j]]=tim[i]+1;
				phi[i*prime[j]]=prime[j]*phi[i];
				break;
			}
			else{
				mpp[i*prime[j]]=prime[j];
				tim[i*prime[j]]=1;
				phi[i*prime[j]]=(prime[j]-1)*phi[i];
			}
		}
	}
}

int T,cas=0;

int main(){
	Euler();
	for(int i=1;i<10;i++)
		cout<<f[i]<<endl;
	scanf("%d",&T);
	for(int i=1;i<MAX_N;i++)
		sum[i]=sum[i-1]+i*f[i]/2;
	while(T--){
		int n;
		scanf("%d",&n);
		printf("Case %d: %llu\n",++cas,sum[n]);
	}
	return 0;
}