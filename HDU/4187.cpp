#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>
#define MAX_N 360005
using namespace std;

typedef long long ll;
typedef long long LL;
ll S,P;

ll A[MAX_N],str[MAX_N];
int nex[MAX_N];

ll prime[MAX_N],tot=0;
bool check[MAX_N];
ll phi[MAX_N];

const ll mod=100000007;

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

ll solve(ll n){
	return Pow(S,n);
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
		res=(res+(LL)solve(n/(*it))*phi[*it]%mod)%mod;
	return res*(LL)getInv(n,mod)%mod;
}

int getnex(int len){    
	memset(nex,0,sizeof(nex));  
    int i=0,j=-1;
    nex[0]=-1;
    while(i<len){
        if(j==-1 || str[i]==str[j]){
            i++;j++;
            nex[i]=j;
        }
        else
            j=nex[j];
    }
    int res=len;
    if(nex[len]&&len%(len-nex[len])==0)
    	res=len-nex[len];
    return len/res;
}

int main(){
	Euler();
	while(scanf("%I64d%I64d",&S,&P)==2){
		if(S==-1)break;
		for(int i=1;i<=P;i++)
			scanf("%I64d",&A[i]);
		sort(A+1,A+1+P);
		for(int i=2;i<=P;i++)
			str[i-1]=A[i]-A[i-1];
		str[0]=A[1]+360000-A[P];
		ll t=getnex(P);
		S=Pow(S,P/t);
		printf("%I64d\n",polya(t));
	}
	return 0;
}