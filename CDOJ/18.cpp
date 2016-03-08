#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdio>
#define INF 100861100
using namespace std;

const double pi=acos(-1);
double a,b,h;
double f(double x){
	double t=a*exp(-x*x)+b*sqrt(x);
	return t*t;
}

double get(double aa,double bb){
	return (bb-aa)/6*(f(aa)+4*f((aa+bb)/2)+f(bb));
}

double Int(){
	double t=h/100000;
	double res=0;
	for(double i=0;i<=h-t;i+=t)
		res+=get(i,i+t);
	return pi*res;
}

double V;
int n;

const double eps=1e-4;

int main(){
	scanf("%lf%d",&V,&n);
	double ans=INF;int p;
	for(int i=0;i<n;i++){
		scanf("%lf%lf%lf",&a,&b,&h);
		if(fabs(Int()-V)<ans){
			//cout<<Int()<<endl;
			ans=fabs(Int()-V);
			p=i;
		}
	}
	printf("%d\n",p);
	return 0;
}