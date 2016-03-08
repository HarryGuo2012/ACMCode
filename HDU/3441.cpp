#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#define MAX_N 100005
using namespace std;

typedef long long ll;
typedef long long LL;
ll A,C;

const ll mod=1000000007;
ll prime[MAX_N],tot=0;
bool check[MAX_N];
ll phi[MAX_N];

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
ll getInv(ll a,ll m){
	ll x,y,d;
	d=extendGcd(a,m,x,y);
	if(d==1)
		return (x%m+m)%m;
	else
		return -1;
}

ll Pow(ll a,int x){
	ll res=1;
	while(x){
		if(x&1)res=res*a%mod;
		a=a*a%mod;
		x>>=1;
	}
	return res;
}

void Euler(){
	phi[1]=1;
	for(int i=2;i<MAX_N;i++){
		if(!check[i]){
			prime[tot++]=i;
			phi[i]=i-1;
		}
		for(int j=0;j<tot;j++){
			if(i*prime[j]>=MAX_N)break;
			check[i*prime[j]]=1;
			if(i%prime[j]==0){
				phi[i*prime[j]]=phi[i]*prime[j];
				break;
			}
			else
				phi[i*prime[j]]=phi[i]*(prime[j]-1);
		}
	}
}

ll getPhi(ll n){
	if(n<MAX_N)return phi[n];
	ll res=1;
	for(int i=0;i<tot;i++){
		if(n==1)break;
		ll p=prime[i];
		if(n%p==0){
			n/=p;
			res=(LL)res*(p-1)%mod2;
			while(n%p==0)res=(LL)res*p%mod2,n/=p;
		}
	}
	if(n!=1)res=(LL)res*(n-1)%mod2;
	return res;
}

ll solve(ll n,ll color){
	return Pow(color,n);
}

vector<int> pf;
set<int> fac;

void getPf(int n){
	pf.clear();
	for(int i=0;i<tot;i++){
		while(n%prime[i]==0){
			pf.push_back(prime[i]);
			n/=prime[i];
		}
		if(n==1)break;
	}
	if(n!=1)pf.push_back(n);
}

set<pair<int,int> > se;

void dfs(int now,int i){
	if(se.find(make_pair(now,i))!=se.end())return;
	se.insert(make_pair(now,i));
	fac.insert(now);
	if(i==pf.size())return;
	dfs(now*pf[i],i+1);
	dfs(now,i+1);
}

void getFac(){
	fac.clear();se.clear();
	dfs(1,0);
}

ll polya1(ll n){
	ll cf0=Pow(C,n*n),cf1=Pow(C,n*n/4),cf2=Pow(C,n*n/2),cf3=Pow(C,n*n/4);
	return ((cf0+cf1)%mod+(cf2+cf3)%mod)%mod*getInv(4,mod);
}

ll polya2(ll n,ll color){
	getPf(n);getFac();
	ll res=0;
	for(set<int>::iterator it=fac.begin();it!=fac.end();it++)
		res=(res+mul(solve(n/(*it),color),getPhi(*it),mod))%mod;
	return res/n;
}

int T;

int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%I64d%I64d",&A,&C);
		
	}
	return 0;
}