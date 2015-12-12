#include<iostream>
#include<cstdio>
#include<algorithm>
#define MAX_N 100005
using namespace std;

int a[MAX_N];
int n;

int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++)scanf("%d",&a[i]);
	sort(a,a+n);
	int sum=0;
	int i=0;
	while(i<n&&sum+a[i]<=n-2-i)sum+=a[i++];
	cout<<n-1-i<<endl;
	return 0;
}
