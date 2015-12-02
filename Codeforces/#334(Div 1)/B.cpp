#include<iostream>
#include<cstring>
#include<algorithm>
#define MAX_N 1000006
using namespace std;

bool vis[MAX_N];

typedef long long ll;

ll k,p;
ll mod=1000000007;
void dfs(ll x){
	if(vis[x])return;
	vis[x]=1;
	dfs(k*x%p);
}

ll Pow(ll x,ll t){
	ll res=1;
	while(t){
		if(t&1)res=res*x%mod;
		t>>=1;
		x=x*x%mod;	
	}
	return res%mod;
}

int main(){
	cin.sync_with_stdio(false);
	cin>>p>>k;
	if(k==0){
		cout<<Pow(p,p-1)<<endl;
		return 0;
	}
	if(k==1){
		cout<<Pow(p,p)<<endl;
		return 0;
	}
	ll cnt=0;
	for(int i=1;i<p;i++){
		if(vis[i])continue;
		cnt++;
		dfs(i);
	}
	cout<<Pow(p,cnt)<<endl;
	return 0;
}
