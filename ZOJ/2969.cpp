#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#define MAX_N 1003
using namespace std;

int T;
int n;

int a[MAX_N];
int b[MAX_N];

int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=n;i>=0;i--)
			scanf("%d",&a[i]);
		memset(b,0,sizeof(b));
		for(int i=1;i<=n;i++)
			b[i-1]=a[i]*i;
		int p=n;
		while(b[p]==0&&p>=0)p--;
		if(p==-1)printf("0\n");
		else{
			printf("%d",b[p]);
			for(int i=p-1;i>=0;i--)
				printf(" %d",b[i]);
			printf("\n");
		}
	}
	return 0;
}