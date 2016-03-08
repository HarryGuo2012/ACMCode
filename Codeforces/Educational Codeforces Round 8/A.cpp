#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

int n,b,p;
int x,y;
int main(){
	scanf("%d%d%d",&n,&b,&p);y=n*p;
	while(n>1){
		x+=n/2*(2*b+1);
		n=n/2+n%2;
	}
	cout<<x<<" "<<y<<endl;
	return 0;
}