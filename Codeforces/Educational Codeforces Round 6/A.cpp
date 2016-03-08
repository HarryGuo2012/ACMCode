#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;

int xa,xb,ya,yb;

int main(){
	scanf("%d%d%d%d",&xa,&ya,&xb,&yb);
	int x,y;
	x=abs(xa-xb),y=abs(ya-yb);
	cout<<x+y-min(x,y)<<endl;
	return 0;
}