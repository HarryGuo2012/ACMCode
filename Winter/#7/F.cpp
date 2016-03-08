#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cstdio>
#define MAX_N 5003
using namespace std;

string s,t;
int S[MAX_N],T[MAX_N];

int n,m;

typedef long long ll;
const ll mod=1000000007;

ll dp[MAX_N][MAX_N];

int main(){
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	cin>>s>>t;
	n=s.length(),m=t.length();
	for(int i=1;i<=n;i++)
		S[i]=s[i-1]-'a';
	for(int i=1;i<=m;i++)
		T[i]=t[i-1]-'a';
	dp[0][0]=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			if(S[i]==T[j])
				dp[i][j]+=dp[i-1][j-1]+1;
			dp[i][j]+=dp[i][j-1];
			dp[i][j]%=mod;
		}
	ll ans=0;
	for(int i=1;i<=n;i++)
		ans=(ans+dp[i][m])%mod;
	cout<<ans<<endl;
	return 0;
}