#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long ll;

class LineFun{
private:
	ll a,b,c;
	ll exGcd(ll A, ll B, ll &X, ll &Y){
		if(B == 0){
			X = 1;
			Y = 0;
			return A;
		}
		ll r = exGcd(B, A % B, X, Y);
		ll t = X;
		X = Y;
		Y = t - A / B * Y;
		return r;
	}　　
public:
	ll x,y;
	LineFun(ll aa,ll bb,ll cc):a(aa),b(bb),c(cc){}
	bool work(){
		ll d=exGcd(a,b,x,y);
		if(c%d!=0)return false;
		x*=c/d,y*=c/d;
		return true;
	}
};

int main(){
	return 0;
}