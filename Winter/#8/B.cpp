#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

double a[3]={9,4,4};

double n;
double t[3];

const double eps=1e-8;

int main(){
	while(true){
		scanf("%lf",&n);
		for(int i=0;i<3;i++)
			scanf("%lf",&t[i]);
		if(fabs(n)<eps&&fabs(t[0])<eps&&fabs(t[1])<eps&&fabs(t[2])<eps)break;
		double xa=0.0,xb=0.0,ya=0.0,yb=0.0;
		for(int i=0;i<3;i++)
			xa+=max(0.0,t[i]-0.5)*a[i],xb+=min(1000.0,t[i]+0.5)*a[i];
		ya=max(0.0,n-0.5),yb=min(10000.0,n+0.5);
		if(ya>=xb||yb<=xa)printf("no\n");
		else printf("yes\n");
	}
	return 0;
}