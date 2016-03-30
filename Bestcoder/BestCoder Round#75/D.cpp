#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAX_N 5555
using namespace std;

int T,n;

int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		int now=1;
		for(int i=2;i<=n;i++){
			int j=(n-i+1)%i;
			if(j==0)j=i;
			if(now<=i-j)
				now+=j;
			else
				now-=i-j;
		}
		printf("%d\n",now);
	}
	return 0;
}