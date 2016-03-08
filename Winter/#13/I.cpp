#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;

int a[100005];
int n;

long long sum=0;

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	sort(a+1,a+1+n);
	for(int i=1;i<=n;i++){
		if(a[i]>sum+1){
			cout<<sum+1<<endl;
			return 0;
		}
		sum=sum+a[i];
	}
	cout<<sum+1<<endl;
	return 0;
}