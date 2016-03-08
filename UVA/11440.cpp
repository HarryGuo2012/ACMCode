#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <vector>
#define MAX_N 10000007
using namespace std;

int prime[MAX_N],tot=0;
bool check[MAX_N];

typedef long long ll;

ll phi[MAX_N];
ll mod=100000007;

void Euler(){
	phi[1]=1;
	//memset(check,0,sizeof(check));
	for(int i=2;i<MAX_N;i++){
		if(!check[i]){
			prime[tot++]=i;
			phi[i]=(i+mod-1)*phi[i-1]%mod;
		}
		else
			phi[i]=i*phi[i-1]%mod;

		for(int j=0;j<tot;j++){
			if(prime[j]*i>=MAX_N)break;
			check[prime[j]*i]=1;
			if(i%prime[j]==0)break;
		}
	}
}

ll Pow(ll a,ll x){
	ll res=1;
	while(x){
		if(x&1)res=res*a%mod;
		a=a*a%mod;;
		x>>=1;
	}
	return res;
}

ll getPow(ll a,ll p){
	ll res=0;
	while(a){
		res+=a/p;
		a/=p;
	}
	return res;
} 

ll N,M;

int main(){
	Euler();
	//cout<<"haha"<<endl;
	while(scanf("%lld%lld",&N,&M)==2){
		if(N==0&&M==0)break;
		ll ans=1;
		for(int i=M+1;i<=N;i++)
			ans=(ans*i)%mod;
		ans=ans*phi[M]%mod;
		printf("%lld\n",(ans-1+mod)%mod);
	}
	return 0;
}