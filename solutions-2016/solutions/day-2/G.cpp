#include<cstdio>
#include<limits>
#include<algorithm>
using namespace std;
typedef long long lint;
struct eInt{ lint x,y;
	eInt(){}
	eInt(lint x,lint y):x(x),y(y){}
	const eInt operator+(const eInt& r)const{
		return eInt(x+r.x,y+r.y);
	}
	const eInt operator-(const eInt& r)const{
		return eInt(x-r.x,y-r.y);
	}
	const eInt operator*(const eInt& r)const{
		const lint x1x2=x*r.x;
		return eInt(x1x2-y*r.y, x1x2-(x-y)*(r.x-r.y));
	}
	const eInt operator/(const eInt&r) const{
		const eInt t = operator*(eInt(r.x-r.y, -r.y));
		const lint n = r.norm();
		return eInt(ldiv(t.x, n),ldiv(t.y, n));
	}
	const lint norm()const{
		return x*(x-y)+y*y;
	}
	bool is_zero()const{
		return !(x||y);
	}
	static lint ldiv(lint a, lint b){
		return a<0?-((b-1-a)/b) : a/b;
	}
	static eInt gcd(eInt a,eInt b) {
		if (b.is_zero()) return a;
		eInt k=a/b,r;
		lint m=numeric_limits<lint>::max();
		for(int dx=0;dx<=1;++dx)for(int dy=0;dy<=1;++dy) {
			eInt t = a-b*eInt(k.x+dx,k.y+dy);
			lint l = t.norm();
			if(m>l){
				m=l;
				r=t;
			}
		}
		return gcd(b,r);
	}
};

const eInt unit[] = {eInt(1,0),eInt(-1,0),eInt(0,1),eInt(0,-1),eInt(1,1),eInt(-1,-1)};


int main(){
	int T,a,b,c,d;
	scanf("%d",&T);
	for(;T--;){
		scanf("%d %d %d %d",&a,&b,&c,&d);
		const eInt g=eInt::gcd(
			eInt(a, b),
			eInt(c, d));
		eInt res; lint len=-1;
		for(size_t i=(sizeof unit)/(sizeof unit[0]);i--;) {
			const eInt t= g*unit[i];
			lint tt=t.x*t.x+t.y*t.y;
			if(tt>len || tt==len && (t.x>res.x || t.x==res.x && t.y>res.y )) {
				res=t;len=tt;
			}
		}
		printf("%lld %lld\n",res.x,res.y);
	}
}

