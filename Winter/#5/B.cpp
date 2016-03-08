#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdio>
#define MAX_N 15
#define INF 1234567890
using namespace std;

double sqr(double x){
	return x*x;
}

const double g=1.0;
const double eps=1e-6;
struct STDLine{
	double a,b;//y=-a*sqr(x)+b;
	STDLine(double x0,double x,double y){
		a=y/(sqr(x0)-sqr(x));
		b=a*sqr(x0);
	}
	STDLine(){}
	double getVal(double x){
		return -a*sqr(x)+b;
	}
	bool check(double x,double h){
		double y=getVal(x);
		if(fabs(y-h)<eps)return true;
		return y>h;
	}
	double getSpeed(){
		return sqrt(g/(2*a)+2*g*b);
	}
};

int n;
double d,b;

double p[MAX_N],h[MAX_N];

double Move(double x,double L){
	int j=0;
	while(j*L<x)j++;
	return x-(j-1)*L-L/2;
}

double ans=INF;

void solve(int t){
	double L=d/t;
	for(int i=0;i<n;i++){
		double np=Move(p[i],L);
		if(fabs(L/2-np)<eps)continue;
		STDLine sl=STDLine(L/2,np,h[i]);
		bool flag=true;
		for(int j=0;j<n;j++)
			if(!sl.check(Move(p[j],L),h[j])){
				flag=false;
				break;
			}
		if(flag)ans=min(ans,sl.getSpeed());
	}
	STDLine sl;
	sl.a=1/L;
	sl.b=L/4;
	bool flag=true;
	for(int j=0;j<n;j++)
		if(!sl.check(Move(p[j],L),h[j])){
			flag=false;
			break;
		}
	if(flag)ans=min(ans,sl.getSpeed());
}

int main(){
	scanf("%lf%d%lf",&d,&n,&b);
	for(int i=0;i<n;i++)
		scanf("%lf%lf",&p[i],&h[i]);
	for(int i=1;i<=b+1;i++)
		solve(i);
	printf("%.5f\n",ans);
	return 0;
}
