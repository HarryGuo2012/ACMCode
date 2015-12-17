#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdio>
#include<iomanip>
using namespace std;

double h,l,v;

const double eps=1e-8;
const double pi=acos(-1);


double f(double x){
	return h+l*tan(x)-9.8/2*l*l/(v*v*cos(x)*cos(x));
}

int main(){
	while(cin>>h>>l>>v){
		if(abs(h)<eps)break;
		double L=atan(v*v/9.8/l);
		cout<<setprecision(2)<<fixed<<f(L)<<endl;
	}
	return 0;
}
