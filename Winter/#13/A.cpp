#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <set>
#define MAX_N 100005
using namespace std;

int a[MAX_N];
int n,m;
set<int> se;

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	int cnt=0;
	for(int i=n;i>=1;i--){
		if(cnt==m)break;
		if(se.find(a[i])!=se.end())continue;
		se.insert(a[i]);
		cnt++;
		printf("%d\n",a[i]);
	}
	return 0;
}