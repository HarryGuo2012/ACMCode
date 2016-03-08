#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;

int a,b;

int dp[1000][1000];

void dfs(int x,int y){
	if(y-2>=0&&dp[x+1][y-2]<dp[x][y]+1){
		dp[x+1][y-2]=dp[x][y]+1;
		dfs(x+1,y-2);
	}
	if(x-2>=0&&dp[x-2][y+1]<dp[x][y]+1){
		dp[x-2][y+1]=dp[x][y]+1;
		dfs(x-2,y+1);
	}
}

int main(){
	int ans=0;
	cin>>a>>b;
	dfs(a,b);
	for(int i=0;i<1000;i++)
		ans=max(ans,max(max(dp[i][0],dp[i][1]),max(dp[0][i],dp[1][i])));
	cout<<ans<<endl;
	return 0;
}