#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
#include<string>
#include<cstdlib>
#include<vector>
#define MAX_L 62
using namespace std;

long long dp[MAX_L][MAX_L][2];

int K[MAX_L];

int getOne(int x){
	int res=0;
	while(x){
		if(x&1)res++;
		x>>=1;
	}
	return res;
}

void dfs(int i,int x){
	if(x==1)return;
	K[i]++;
	x=getOne(x);
	dfs(i,x);
}

int kk;

long long work(long long n){
	memset(dp,0,sizeof(dp));
	dp[0][0][0]=1;
	if(n&1)dp[0][1][0]=1;
	else dp[0][1][1]=1;
	for(int i=1;i<MAX_L;i++){
		for(int j=0;j<MAX_L;j++){
			int t=(n>>i)&1;
			if(t){
				dp[i][j][0]+=dp[i-1][j][0]+dp[i-1][j][1];
				if(j>0)dp[i][j][0]+=dp[i-1][j-1][0];
				if(j>0)dp[i][j][1]+=dp[i-1][j-1][1];
			}
			else{
				dp[i][j][0]+=dp[i-1][j][0];
				dp[i][j][1]+=dp[i-1][j][1];
				if(j>0)dp[i][j][1]+=dp[i-1][j-1][0]+dp[i-1][j-1][1];
			}
		}
	}
	long long ans=0;
	for(int i=1;i<MAX_L;i++)
		if(K[i]==kk)
			ans+=dp[MAX_L-1][i][0];
	return ans;
}

int work2(int n){
	int res=0;
	for(int i=1;i<=n;i++)if(K[i]==kk+1)res++;
	return res;
}

int main(){
	for(int i=1;i<MAX_L;i++)
		dfs(i,i);
	long long L,R;
	while(true){
		scanf("%lld%lld%lld",&L,&R,&kk);
		if(L==0&&R==0&&kk==0)break;
		kk--;
		if(kk==-1){
			if(L==1)cout<<1<<endl;
			else cout<<0<<endl;
			continue;
		}
		if(L==1&&kk==0)
			cout<<work(R)-work(L-1)-1<<endl;
		else
			cout<<work(R)-work(L-1)<<endl;
	}
	return 0;
}
