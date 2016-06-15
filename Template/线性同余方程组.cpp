#include <iostream>
#include <cstring>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <stack>
#define MAX_N 500005
using namespace std;

typedef long long ll;

class LineFun{
private:
	ll a,b,c;
	ll exGcd(ll A,ll B,ll &X,ll &Y){
		if(B==0){X=1,Y=0;return A;}
		ll r=exGcd(B,A%B,X,Y);
		ll t=X;
		X=Y,Y=t-A/B*Y;
		return r;
	}
public:
	ll x,y;
	LineFun(ll aa,ll bb,ll cc):a(aa),b(bb),c(cc){}
	LineFun(){}
	bool work(){
		ll d=exGcd(a,b,x,y);
		if(c%d!=0)return false;
		x*=c/d,y*=c/d;
		return true;
	}
}LF;

class LineFuns{
public:
	stack<pair<ll,ll> > st;
	ll x,M;
	void init(){
		while(st.size())st.pop();
	}
	bool work(){
		while(st.size()>1){
			ll d1=st.top().first,m1=st.top().second;st.pop();
			ll d2=st.top().first,m2=st.top().second;st.pop();
			LF=LineFun(m1,-m2,d2-d1);
			if(LF.work()==false)return false;
			ll dx=LF.x*m1+d1,mx=m1*m2/__gcd(m1,m2);
			st.push(make_pair(dx,mx));
		}
		ll d=st.top().first,m=st.top().second;st.pop();
		LF=LineFun(1,m,d);
		if(LF.work()==false)return false;
		x=LF.x,M=m;
		x+=abs(x)/M*M;x=(x+M)%M;
		return true;
	}
}LFS;

int main(){
	return 0;
}