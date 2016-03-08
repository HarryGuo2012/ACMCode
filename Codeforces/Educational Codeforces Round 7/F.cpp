#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <queue>
#define MAX_N 1000006
using namespace std;

typedef long long ll;
ll n,k;

const ll mod=1000000007;

ll A;

ll fra[MAX_N],L[MAX_N];
ll y[MAX_N];

ll Pow(ll a,ll x){
	ll res=1;
	while(x){
		if(x&1)res=res*a%mod;
		a=a*a%mod;
		x>>=1;
	}
	return res;
}

int main(){
	fra[0]=1;
	for(int i=1;i<MAX_N;i++)
		fra[i]=fra[i-1]*i%mod;
	cin>>n>>k;
	if(n<=k+5){
		ll ans=0;
		for(int i=1;i<=n;i++)
			ans=(Pow(i,k)+ans)%mod;
		cout<<ans<<endl;
		return 0;
	}
	A=1;
	for(int i=0;i<=k+1;i++)
		A=A*(n-i)%mod;
	for(int j=0;j<=k+1;j++){
		bool flag=false;
		if((k-j+1)&1)flag=true;
		L[j]=A*Pow((n-j)%mod*fra[j]%mod*fra[k+1-j]%mod,mod-2)%mod;
		if(flag)L[j]=-L[j];
	}
	for(int j=1;j<=k+1;j++)
		y[j]=(y[j-1]+Pow(j,k))%mod;
	ll ans=0;
	for(int i=0;i<=k+1;i++)
		ans=(ans+y[i]*L[i]%mod)%mod;
	ans=(ans%mod+mod)%mod;
	cout<<ans<<endl;
	//cin>>n;
	return 0;
}