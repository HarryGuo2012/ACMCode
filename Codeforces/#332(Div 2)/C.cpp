#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<climits>
#define INF INT_MAX
#define MAX_N 100005
using namespace std;

int n;
int h[MAX_N];
int dp[MAX_N];

int main(){
	cin.sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>h[i];
	dp[n]=h[n];
	int cnt=0;
	for(int i=n-1;i>=1;i--)dp[i]=min(h[i],dp[i+1]);
	int now=0;
	for(int i=1;i<=n-1;i++){
		now=max(now,h[i]);
		if(now<=dp[i+1]){
			cnt++;
			now=0;
		}
	}
	cout<<cnt+1<<endl;
	return 0;
}
