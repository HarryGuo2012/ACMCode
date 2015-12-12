#include<cstring>
#include<vector>
#include<queue>
#include<iostream>
#include<cmath>
#include<cstdio>
#include<algorithm>
#include<climits>
using namespace std;

typedef long long ll;

ll mx=-1,my=-1;

ll N;
ll mmx=LLONG_MAX,mmy=LLONG_MAX;

int main(){
	scanf("%lld",&N);
	for(int i=0;i<N;i++){
		ll x,y;
		scanf("%lld%lld",&x,&y);
		mx=max(mx,x);
		my=max(my,y);
		mmx=min(mmx,x);
		mmy=min(mmy,y);
	}
	ll m=max(mx-mmx,my-mmy);
	printf("%lld\n",m*m);
	return 0;
}
