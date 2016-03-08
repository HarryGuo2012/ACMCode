#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <climits>
#include <cmath>
#define INF LLONG_MAX
using namespace std;

int T;
typedef long long ll;

ll n,m;
ll a[3],b[3];

ll d(ll i,ll j){
	return abs(i-j);
}

int main(){
	scanf("%d",&T);
	ll sum=0;
	while(T--){
		scanf("%I64d%I64d",&n,&m);
		for(int i=1;i<=3;i++)
			scanf("%I64d%I64d",&a[i],&b[i]);
		sum=0;ll now=0;
		while(m--){
			now++;
			ll s,t;scanf("%I64d%I64d",&s,&t);
			ll ans=d(s,t);
			for(int i=1;i<=3;i++){
				ans=min(ans,d(s,a[i])+d(b[i],t)+1);
				ans=min(ans,d(s,b[i])+d(a[i],t)+1);
			}
			for(int i=1;i<=3;i++)
				for(int j=1;j<=3;j++){
					if(i==j)continue;
					ans=min(ans,d(s,a[i])+d(b[i],a[j])+d(b[j],t)+2);
					ans=min(ans,d(s,b[i])+d(a[i],a[j])+d(b[j],t)+2);
					ans=min(ans,d(s,a[i])+d(b[i],b[j])+d(a[j],t)+2);
					ans=min(ans,d(s,b[i])+d(a[i],b[j])+d(a[j],t)+2);
				}
			for(int i=1;i<=3;i++)
				for(int j=1;j<=3;j++)
					for(int k=1;k<=3;k++){
						if(i==j||j==k||i==k)continue;
						ans=min(ans,d(s,a[i])+d(b[i],a[j])+d(b[j],a[k])+d(b[k],t)+3);
						ans=min(ans,d(s,b[i])+d(a[i],a[j])+d(b[j],a[k])+d(b[k],t)+3);
						ans=min(ans,d(s,a[i])+d(b[i],b[j])+d(a[j],a[k])+d(b[k],t)+3);
						ans=min(ans,d(s,b[i])+d(a[i],b[j])+d(a[j],a[k])+d(b[k],t)+3);
						ans=min(ans,d(s,a[i])+d(b[i],a[j])+d(b[j],b[k])+d(a[k],t)+3);
						ans=min(ans,d(s,b[i])+d(a[i],a[j])+d(b[j],b[k])+d(a[k],t)+3);
						ans=min(ans,d(s,a[i])+d(b[i],b[j])+d(a[j],b[k])+d(a[k],t)+3);
						ans=min(ans,d(s,b[i])+d(a[i],b[j])+d(a[j],b[k])+d(a[k],t)+3);
					}
			sum=(sum+ans*now%1000000007)%1000000007;
		}
		printf("%I64d\n",sum);
	}
	return 0;
}