#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <cstdio>
#define MAX_N 100005
using namespace std;

typedef long long ll;
typedef long long LL;

ll mod;
ll mod2;
ll mod3;

ll mul(ll a,ll b,ll m){
	bool flag=false;
	if(b<0){
		flag=true;
		b=-b;
	}
	ll res=0;
	while(b){
		if(b&1)res=(res+a)%m;
		a=(a+a)%m;
		b>>=1;
	}
	if(flag)return ((-res)%m+m)%m;
	return res;
}

struct Matrix{
	ll ma[3][3];
	Matrix(){
		memset(ma,0,sizeof(ma));
	}
	Matrix operator*(Matrix M){
		Matrix res;
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				for(int k=0;k<3;k++)
					res.ma[i][j]=(res.ma[i][j]+mul(ma[i][k],M.ma[k][j],mod))%mod;
		return res;
	}
};

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
			res=(LL)res*(p-1)%mod2;
			while(n%p==0)res=(LL)res*p%mod2,n/=p;
		}
	}
	if(n!=1)res=(LL)res*(n-1)%mod2;
	return res;
}

Matrix Pow(Matrix a,ll x){
	Matrix res;
	res.ma[0][0]=res.ma[1][1]=res.ma[2][2]=1;
	while(x){
		if(x&1)res=res*a;
		a=a*a;
		x>>=1;
	}
	return res;
}

ll solve(ll n){
	if(n==1)return 1%mod2;
	if(n==2)return 5%mod2;
	mod=mod2;
	Matrix tmp;
	tmp.ma[0][0]=3,tmp.ma[0][1]=-1,tmp.ma[0][2]=2;
	tmp.ma[1][0]=1,tmp.ma[2][2]=1;
	Matrix a=Pow(tmp,n-2);
	return ((mul(a.ma[0][0],5,mod)+a.ma[0][1])%mod+a.ma[0][2])%mod;
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
	mod2=mod3*n;
	for(set<int>::iterator it=fac.begin();it!=fac.end();it++)
		res=(res+mul(solve(n/(*it)),getPhi(*it),mod2))%mod2;
	return res/n;
}

ll N;

int main(){
	Euler();
	//cout<<solve(1)<<" "<<solve(2)<<endl;
	//cout<<solve(4)<<endl;
	while(scanf("%I64d%I64d",&N,&mod3)==2){
		printf("%I64d\n",polya(N));
	}
	return 0;
}