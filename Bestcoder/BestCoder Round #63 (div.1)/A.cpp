#include<iostream>
#include<cstring>
#include<algorithm>
#include<set>
#define MAX_N 123
using namespace std;

typedef long long ll;
ll dp[MAX_N][MAX_N];
ll n,k;

ll a[MAX_N];

set<int> vis;

int main(){
	cin.sync_with_stdio(false);
	while(cin>>n>>k&&n&&k){
		for(int i=1;i<=n;i++)cin>>a[i];
		memset(dp,0,sizeof(dp));
		for(int i=1;i<=n;i++)dp[i][1]=1;
		for(int i=1;i<=n;i++)
			for(int j=2;j<=k;j++){
				for(int t=i-1;t>=1;t--){
					if(a[t]<a[i]&&vis.find(a[t])==vis.end()){
						dp[i][j]+=dp[t][j-1];
						vis.insert(a[t]);
					}
				}
				vis.clear();
			}
		ll ans=0;
		for(int i=1;i<=n;i++)ans+=dp[i][k];
		cout<<ans<<endl;
	}
	return 0;
}
