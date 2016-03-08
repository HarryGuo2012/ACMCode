#include <iostream>
#include <cstring>
#include <cmath>
#include <cstdio>
using namespace std;

double a,b,c;

double xa,xb;

int main(){
	cin>>a>>b>>c;
	double d=b*b-4*a*c;
	xa=(-b+sqrt(d))/(2*a);
	xb=(-b-sqrt(d))/(2*a);
	if(xb>xa)swap(xa,xb);
	printf("%.7f\n%.7f\n",xa,xb);
	return 0;
}