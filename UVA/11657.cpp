#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <algorithm>
using namespace std;

typedef long long ll;

ll m,n,xa,ya,xb,yb,p,q;

ll x[4],y[4];

int main(){
	//cout<<__gcd(12,-6)<<endl;
	while(true){
		scanf("%lld%lld%lld%lld%lld%lld%lld%lld",&m,&n,&xa,&ya,&xb,&yb,&p,&q);
		if(m==0&&n==0)break;
		if(p<0)xa=m-xa,xb=m-xb,p=-p;
		if(q<0)ya=n-ya,yb=n-yb,q=-q;
		if(p==0){
			if(xa==xb)
				printf("HIT\n");
			else
				printf("MISS\n");
			continue;
		}
		if(q==0){
			if(ya==yb)
				printf("HIT\n");
			else
				printf("MISS\n");
			continue;
		}
		ll c=-q*xa+p*ya;
		x[0]=xb,x[1]=xb,x[2]=-xb,x[3]=-xb;
		y[0]=yb,y[1]=-yb,y[2]=yb,y[3]=-yb;

		bool flag=false;
		for(int i=0;i<4;i++){
			ll A=2*q*m,B=-2*p*n,D=(-q*x[i]+p*y[i]-c); 
			ll d=__gcd(A,B);
			//cout<<A<<" "<<B<<" "<<D<<" "<<d<<endl;
			if(D%d==0)
				flag=true;
		}
		if(flag)printf("HIT\n");
		else printf("MISS\n");
	}
	return 0;
}