#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

typedef long long ll;

ll A,B,n;
ll L,t,m;

ll f(ll x){
	ll a=(A+(L-1)*B+A+(x-1)*B)*(x-L+1);
	ll b=2*m;
	ll ans;
	if(a%b)ans=a/b+1;
	else ans=a/b;
	ans=max(ans,A+(x-1)*B);
	return ans;
}

int main(){
	scanf("%I64d%I64d%I64d",&A,&B,&n);
	while(n--){
		scanf("%I64d%I64d%I64d",&L,&t,&m);
		if(f(L)>t){
			puts("-1");
			continue;
		}
		ll l=L,r=2*m*t+L+100;
		while(r-l>1){
			ll mid=(l+r)>>1;
			if(f(mid)<=t)l=mid;
			else r=mid;
		}
		printf("%I64d\n",l);
	}
	return 0;
}
