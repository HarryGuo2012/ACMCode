#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
#include<cstdio>
#define MAX_N 2003
#define MAX_M 123
using namespace std;

int n,m;
int a[MAX_N];

int b[MAX_M][MAX_N];

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		for(int j=1;j<=m;j++)
			b[j][i]=b[j][i-1]+(j==a[i]);
	}
	int q;
	scanf("%d",&q);
	while(q--){
		int l,r;
		scanf("%d%d",&l,&r);
		int ans=0;
		for(int i=1;i<=m;i++){
			ans+=(b[i][r]-b[i][l-1]>0);
		}
		printf("%d\n",ans);
	}
	return 0;
}
