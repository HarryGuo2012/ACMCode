#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#include<climits>
#define INF INT_MAX
#define MAX_N 200005
using namespace std;

int a[MAX_N];

int n;

int ans=INF;

int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++)scanf("%d",&a[i]);
	sort(a,a+n);
	for(int i=0;i<n;i++){
		int j=i+n/2;
		if(j>=n)break;
		ans=min(ans,a[j]-a[i]);
	}
	cout<<ans<<endl;
	return 0;
}
