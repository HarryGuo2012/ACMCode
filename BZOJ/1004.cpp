#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <vector>
#define MAX_N 123
using namespace std;

typedef long long ll;

int sr,sb,sg,m,p;
int n;
ll cf[MAX_N];

int pe[MAX_N],cnt;
bool vis[MAX_N];

int cs[MAX_N],tot=0;
ll S[MAX_N];

void dfs(int i){
	if(vis[i])return;
	cnt++;vis[i]=1;
	dfs(pe[i]);
}

ll dp[MAX_N][MAX_N][MAX_N];

ll getCf(){
	memset(S,0,sizeof(S));
	for(int i=1;i<=tot;i++)
		S[i]=(S[i-1]+cs[i])%p;
	memset(dp,0,sizeof(dp));
	dp[0][0][0]=1;
	for(int i=1;i<=tot;i++)
		for(int r=0;r<=sr;r++)
			for(int b=0;b<=sb;b++){
				if(r-cs[i]>=0)dp[i][r][b]+=dp[i-1][r-cs[i]][b];
				if(b-cs[i]>=0)dp[i][r][b]+=dp[i-1][r][b-cs[i]];
				if(S[i]-r-b-cs[i]>=0)dp[i][r][b]+=dp[i-1][r][b];
				dp[i][r][b]%=p;
			}
	return dp[tot][sr][sb]%p;
}

ll Pow(ll a,ll x){
	ll res=1;
	while(x){
		if(x&1)res=res*a%p;
		a=a*a%p;
		x>>=1;
	}
	return res;
}

ll getInv(ll x){
	return Pow(x,p-2)%p;
}

int main(){
	scanf("%d%d%d%d%d",&sr,&sb,&sg,&m,&p);
	n=sr+sb+sg;
	m++;
	for(int i=1;i<=m;i++){
		if(i!=m)
			for(int j=1;j<=n;j++)
				scanf("%d",&pe[j]);
		else
			for(int j=1;j<=n;j++)
				pe[j]=j;
		memset(vis,0,sizeof(vis));
		tot=0;
		for(int j=1;j<=n;j++){
			if(vis[j])continue;
			cnt=0;
			dfs(j);
			cs[++tot]=cnt;
		}
		cf[i]=getCf();
	}
	ll ans=0;
	for(int i=1;i<=m;i++)
		ans=(ans+cf[i])%p;
	cout<<ans*getInv(m)%p<<endl;
	//cin>>n;
	return 0;
}