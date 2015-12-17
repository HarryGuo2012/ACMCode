#include<iostream>
#include<cstring>
#include<vector>
#include<cstdio>
#include<algorithm>
#define MAX_N 100005
using namespace std;

int n,m;

int a[MAX_N];

int main(){
	scanf("%d%d",&n,&m);
	if(m*7<n){
		cout<<-1<<endl;
		return 0;
	}
	for(int i=1;i<=m;i++)
		a[i]=1,n-=2;
	if(n<0){
		cout<<-1<<endl;
		return 0;
	}
	
	for(int i=1;i<=m;i++){
		if(n>=4){
			a[i]=9;
			n-=4;
		}
		else if(n>=1){
			a[i]=7;
			n--;
		}
		else break;
	}
	if(a[m]==7){
		if(n==1)a[m]=4;
		else if(n==2) a[m]=5;
	}
	else if(a[m]==9){
		for(int i=m;i>=1&&n;i--)
			a[i]=8,n--;
	}
	for(int i=1;i<=m;i++)
		printf("%d",a[i]);
	printf("\n");
	return 0;
}
