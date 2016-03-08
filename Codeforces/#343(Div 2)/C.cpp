#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <string>
using namespace std;

int n,m;
string s;

typedef long long ll;
ll u,v;

ll C[2222][2222];

const ll mod=1000000007;

int main(){
	C[0][0]=1;
	for(int i=1;i<2222;i++)
		for(int j=0;j<=i;j++){
			if(j==0)C[i][j]=1;
			else C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
		}
	cin.sync_with_stdio(false);
	cin>>n>>m>>s;
	if(n&1){
		cout<<0<<endl;
		return 0;
	}
	ll maxLeft=0,maxRight=0;
	for(int i=0;i<s.length();i++){
		if(s[i]=='(')u++;
		else v++;
		maxLeft=max(maxLeft,v-u);
	}
	u=0,v=0;
	for(int i=s.length()-1;i>=0;i--){
		if(s[i]==')')v++;
		else u++;
		maxRight=max(maxRight,u-v);
	}
	ll ans=0;
	for(ll x=0;x+u<=n/2;x++)
		for(ll y=0;y<=x-maxLeft;y++){
			if(y+v>n/2)break;
			ll a=n/2-x-u,b=n/2-v-y;
			if(a+maxRight>b)continue;
			ll tmp=(C[x+y][x]-C[x+y][x+1]+mod)%mod*((C[a+b][b]-C[a+b][b+1]+mod)%mod)%mod;
			ans=(ans+tmp)%mod;
		}
	cout<<ans%mod<<endl;cin>>n;
	return 0;
}