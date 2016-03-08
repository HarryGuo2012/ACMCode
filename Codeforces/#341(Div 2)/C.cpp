#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#define MAX_N 100005
using namespace std;

typedef long long ll;

ll l[MAX_N],r[MAX_N],a[MAX_N];

int n;
ll p;

double ans;

int main(){
	cin.sync_with_stdio(false);
	cin>>n>>p;
	for(int i=0;i<n;i++){
		cin>>l[i]>>r[i];
		a[i]=r[i]/p-(l[i]-1)/p;
	}

	for(int i=0;i<n;i++){
		int u=i,v=(i+1)%n;
		ans+=(a[u]*(r[v]-l[v]+1)+a[v]*(r[u]-l[u]+1.0)-a[u]*a[v])*2000.0/((r[u]-l[u]+1)*(r[v]-l[v]+1.0));
	}
	printf("%.7f\n",ans);
	return 0;
}