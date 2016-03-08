#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#define MAX_N 1003
using namespace std;

int n;
long long a[MAX_N],b[MAX_N];

int main(){
	cin.sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=n;i++)
		cin>>b[i];
	long long ans=0;
	long long A=0,B=0;
	for(int i=1;i<=n;i++)
		A|=a[i],B|=b[i];
	ans=A+B;
	cout<<ans<<endl;
	return 0;
}