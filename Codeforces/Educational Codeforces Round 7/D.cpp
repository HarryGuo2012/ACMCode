#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#define MAX_N 1000006
using namespace std;

int n;

int main(){
	scanf("%d",&n);
	if(n&1){
		for(int i=2;i<n;i+=2)
			printf("%d ",i);
		for(int i=n-1;i>=2;i-=2)
			printf("%d ",i);
		for(int i=1;i<n;i+=2)
			printf("%d ",i);
		printf("%d ",n);
		for(int i=n-2;i>=1;i-=2)
			printf("%d ",i);
		printf("%d\n",n);
	}
	else{
		for(int i=1;i<n;i+=2)
			printf("%d ",i);
		for(int i=n-1;i>=1;i-=2)
			printf("%d ",i);
		for(int i=2;i<n;i+=2)
			printf("%d ",i);
		printf("%d ",n);
		for(int i=n-2;i>=2;i-=2)
			printf("%d ",i);
		printf("%d\n",n);
	}
	return 0;
}