#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

double c=1.000000011;
double n,t;

int main(){
	scanf("%lf%lf",&n,&t);
	printf("%.7f\n",n*pow(c,t));
}