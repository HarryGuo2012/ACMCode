#include <iostream>
#include <iomanip>
#include <cstring>
#include <vector>
#include <queue>
#include <cstdio>
#include <algorithm>
#define MAX_N 1000006
using namespace std;

int n,k;

typedef int ll;

ll c[MAX_N],v[MAX_N];

ll minSt[MAX_N][25];
ll maxSt[MAX_N][25];
int Log[MAX_N];
double ans=0.0;

void init(){
	Log[1]=0;
	for(int i=2;i<MAX_N;i++){
		if((1<<(Log[i-1]+1))==i)Log[i]=Log[i-1]+1;
		else Log[i]=Log[i-1];
	}
	for(int i=1;i<=n;i++){
		maxSt[i][0]=v[i];
		minSt[i][0]=c[i];
	}
	for(int j=1;j<25;j++)
		for(int i=1;i<=n;i++){
			minSt[i][j]=min(minSt[i][j-1],minSt[min(i+(1<<(j-1)),n)][j-1]);
			maxSt[i][j]=max(maxSt[i][j-1],maxSt[min(i+(1<<(j-1)),n)][j-1]);
		}
}

ll queryMin(int l,int r){
	int t=Log[r-l+1];
	return min(minSt[l][t],minSt[r-(1<<t)+1][t]);
}

ll queryMax(int l,int r){
	int t=Log[r-l+1];
	return max(maxSt[l][t],maxSt[r-(1<<t)+1][t]);
}

vector<ll> ve;

double dp[MAX_N];

int main(){
	cin.sync_with_stdio(false);
	ve.push_back(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>v[i];
		v[i]*=100;
	}
	for(int i=1;i<=n;i++)
		cin>>c[i];
	init();
	for(int i=1;i<=n;i++){
		if(queryMax(i,n)<queryMin(i,n)){
			ve.push_back(queryMax(i,n));
			continue;
		}
		int l=i-1,r=n;
		while(r-l>1){
			int m=(l+r)>>1;
			if(queryMin(i,m)<=queryMax(i,m))r=m;
			else l=m;
		}
		ll tmp=0;
		if(r>i)tmp=queryMax(i,r-1);
		tmp=max(tmp,queryMin(i,r));
		ve.push_back(tmp);
	}
	sort(ve.begin()+1,ve.end());
	for(int i=1;i<ve.size();i++){
		if(n-i+2-k==0)break;
		if(i==1)
			dp[1]=(double)k/n;
		else
			dp[i]=dp[i-1]*(double)(n-i+2-k)/(n-i+1);
		ans+=dp[i]*ve[i];
	}
	cout<<setprecision(8)<<fixed<<ans<<endl;
	return 0;
}