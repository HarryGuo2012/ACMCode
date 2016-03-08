#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#define MAX_N 4555
using namespace std;

typedef long long ll;

ll cnt[MAX_N];

ll cnt2[MAX_N];

int main(){
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		cnt[u+v]++;
		cnt2[u-v+1002]++;
	}
	long long ans=0;
	for(int i=0;i<MAX_N;i++){
		ans+=cnt[i]*(cnt[i]-1)/2;
		ans+=cnt2[i]*(cnt2[i]-1)/2;
	}
	cout<<ans<<endl;
	//cin>>ans;
	return 0;
}