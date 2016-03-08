#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cstdio>
#define MAX_N 1000006
using namespace std;

typedef long long ll;

ll m=1000000009;

ll s5=(ll)383008016;
ll A=(ll)691504013,B=(ll)308495997,D=(ll)276601605;

ll C[MAX_N];

ll N,K;

ll extendGcd(ll a,ll b,ll &x,ll &y){
	ll ans,t;
	if(b==0){
		x=1;y=0;
		return a;
	}
	ans=extendGcd(b,a%b,x,y);
	t=x;x=y;y=t-(a/b)*y;
	return ans;
}
//返回x，a*x=1(mod m)
ll getInv(ll a){
	ll x,y,d;
	d=extendGcd(a,m,x,y);
	return (x%m+m)%m;
}

ll Pow(ll a,ll x){
	ll res=1;
	while(x){
		if(x&1)res=res*a%m;
		a=a*a%m;
		x>>=1;
	}
	return res%m;
}

int T;

ll getAB(ll i){
	ll res;
	ll q=Pow(A,i)*Pow(B,K-i)%m;
	if(q!=1){
		ll a1=C[i]*q%m;
		res=a1*(Pow(q,N)+m-1)%m*getInv(q-1+m)%m;
	}
	else 
		res=(N%m)*C[i]%m;
	if((K-i)&1)return m-res;
	return res;
}

ll F[MAX_N];

void work(){
	F[1]=1,F[2]=1;
	for(int i=3;i<MAX_N;i++)
		F[i]=(F[i-1]+F[i-2])%m;
	ll res=0;
	for(int i=1;i<=4;i++)
		res=(res+Pow(F[i],20))%m;
	cout<<res<<endl;
}

int main(){
	//work();
	//cout<<getInv(5)<<" "<<getInv(5+m)<<endl;
	scanf("%d",&T);
	while(T--){
		scanf("%lld%lld",&N,&K);
		C[0]=1;
		for(int i=1;i<=K;i++)
			C[i]=C[i-1]*(K-i+1)%m*getInv(i)%m;
		ll res=0;
		for(int i=0;i<=K;i++)
			res=(res+getAB(i))%m;
		printf("%lld\n",(Pow(D,K)*res)%m);
	}
	return 0;
}