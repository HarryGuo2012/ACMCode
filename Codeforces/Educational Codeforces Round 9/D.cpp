#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#define MAX_N 1000006
using namespace std;

int n,m;
int a[MAX_N],cnt[MAX_N];

int tmp[MAX_N];

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		if(a[i]<=m)
			cnt[a[i]]++;
	}
	for(int i=1;i<=m;i++){
		if(cnt[i]==0)continue;
		for(int j=i;j<=m;j+=i)
			tmp[j]+=cnt[i];
	}
	int l=1,k=0;
	for(int i=1;i<=m;i++)
		if(k<tmp[i])l=i,k=tmp[i];
	printf("%d %d\n",l,k);
	for(int i=1;i<=n;i++)
		if(l%a[i]==0)
			printf("%d ",i);
	printf("\n");
	//cin>>n;
	return 0;
}