#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

typedef long long ll;

ll n,m;

ll cnt=0;
ll totCnt=0;

ll C(ll a,ll b,ll x){
	b=min(b,a-b);
	ll res=1;
	ll i=a;
	if(res>=x)return x;
	for(ll k=1;k<=b;k++){
		cnt++;totCnt++;
		if(cnt>100)return 0;
		res=res*i/k;i--;
		if(res>=x)
			return x;
	}
	return res;
}

bool check(ll k){
	cnt=0;
	if(k==0)return 1>=n;
	if(k<30&&n>(1<<k))return 0;
	ll tot=k*m;
	ll i=0,now=0;
	ll whileCnt=0;
	while(tot>0){
		whileCnt++;if(whileCnt>1000){return 0;}
		if(i>k)break;
		ll t=i==0?123456:(tot/i);
		ll tmp=C(k,i,t);
		if(cnt>100)return 0;
		now+=tmp;tot-=tmp*i;
		if(now>=n)return true;
		i++;
	}
	//cout<<k<<" "<<now<<endl;
	return now>=n;
}

int main(){
	cin.sync_with_stdio(false);
	cin>>n>>m;
	ll L=-1,R=n+2;
	ll biCnt=0;
	while(R-L>1){
		if(totCnt>1000000){cout<<"fuck"<<endl;break;}
		biCnt++;
		if(biCnt>1000000){cout<<"shit"<<endl;break;}
		ll mid=(L+R)>>1;
		if(check(mid))R=mid;
		else L=mid;
	}
	cout<<R<<endl;
	//cin>>n;
	return 0;
}