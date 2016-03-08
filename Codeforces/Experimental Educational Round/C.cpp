#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

ll Pow(ll a,ll x){
	ll res=1;
	while(x){
		if(x&1)res*=a;
		a*=a;
		x>>=1;
	}
	return res;
}

int main(){
	ll n=0;
	scanf("%I64d",&n);
	ll ans=0;
	for(int i=1;i<=n;i++)
		ans+=Pow(2,i);
	cout<<ans<<endl;
	return 0;
}