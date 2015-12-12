#include<iostream>
#include<cstring>
#include<algorithm>
#include<set>
#define MAX_N 55
using namespace std;

int need[MAX_N];

set<int> se;

bool check(int i,int j){
	for(int k=0;k<i;k++)if(se.find(need[k]+j)!=se.end())
		return false;
	return true;
}

int a[MAX_N];
int n;

int main(){
	need[0]=1;
	need[1]=2;
	se.insert(3);
	for(int i=2;i<MAX_N;i++){
		int j=need[i-1]+1;
		while(!check(i,j))j++;
		need[i]=j;
		for(int k=0;k<i;k++)se.insert(j+need[k]);
	}
	scanf("%d",&n);
	if(n==2){
		printf("1 1\n");
		return 0;
	}
	for(int i=0;i<n;i++)
		printf("%d ",need[i]);
	printf("\n");
	return 0;
}
