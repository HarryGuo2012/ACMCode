#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <cstdio>
#define MAX_N 100005
using namespace std;

typedef int ll;
typedef long long LL;

ll mod=1000000007;

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

struct Matrix{
	ll ma[2][2];
	Matrix(){
		memset(ma,0,sizeof(ma));
	}
	Matrix operator*(Matrix M){
		Matrix res;
		for(int i=0;i<2;i++)
			for(int j=0;j<2;j++)
				for(int k=0;k<2;k++)
					res.ma[i][j]=(res.ma[i][j]+(LL)ma[i][k]*M.ma[k][j]%mod)%mod;
		return res;
	}
};

ll K;
ll prime[MAX_N],tot=0;
bool check[MAX_N];
ll phi[MAX_N];

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
			res=(LL)res*(p-1)%mod;
			while(n%p==0)res=(LL)res*p%mod,n/=p;
		}
	}
	if(n!=1)res=(LL)res*(n-1)%mod;
	return res;
}

Matrix Pow(Matrix a,ll x){
	Matrix res;
	res.ma[0][0]=res.ma[1][1]=1;
	while(x){
		if(x&1)res=res*a;
		a=a*a;
		x>>=1;
	}
	return res;
}

ll solve(ll n){
	ll f2=(LL)K*(K-1)%mod*(K-2)%mod;
	ll f3=(LL)f2*(K-3)%mod;
	//cout<<f1<<" "<<f2<<endl;
	if(n==1)return 0;
	if(n==2)return f2;
	if(n==3)return f3;
	Matrix a;
	a.ma[0][0]=K-3,a.ma[0][1]=K-2,a.ma[1][0]=1,a.ma[1][1]=0;
	a=Pow(a,n-3);
	return ((LL)a.ma[0][0]*f3%mod+(LL)a.ma[0][1]*f2%mod)%mod;
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

ll polya(ll n){
	getPf(n);getFac();
	ll res=0;
	for(set<int>::iterator it=fac.begin();it!=fac.end();it++)
		res=(res+(LL)solve(n/(*it))*getPhi(*it)%mod)%mod;
	return res*(LL)getInv(n,mod)%mod;
}

ll N;

int main(){
	Euler();
	//cout<<solve(1)<<" "<<solve(2)<<endl;
	//cout<<solve(4)<<endl;
	while(scanf("%d%d",&N,&K)==2){
		printf("%d\n",polya(N));
	}
	return 0;
}