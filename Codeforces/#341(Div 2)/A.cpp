#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#define MAX_N 100005
using namespace std;

int n;
long long a[MAX_N];
long long ans;

int main(){
	cin>>n;
	for(int i=0;i<n;i++)
		cin>>a[i];
	for(int i=0;i<n;i++)ans+=a[i];
	sort(a,a+n);
	if(ans&1){
		int p;
		for(int i=0;i<n;i++)if(a[i]&1){p=i;break;}
		cout<<ans-a[p]<<endl;
	}
	else 
		cout<<ans<<endl;
	return 0;
}