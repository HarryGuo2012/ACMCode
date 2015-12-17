#include<iostream>
#include<cstring>
#include<vector>
#include<cstdio>
#include<string>
#define MAX_N 1000006
using namespace std;

typedef long long ll;
int n,m;
string s;
int y[MAX_N];

bool used[MAX_N];

int main(){
	cin.sync_with_stdio(false);
	cin>>n>>m>>s;
	for(int i=1;i<=m;i++)
		cin>>y[i];
	int k=s.length();
	int j=y[1];
	for(int i=1;i<=m;i++){
		for(int t=j;t<=y[i]+k-1;t++)
			used[t]=1;
		j=max(y[i]+k,y[i+1]);
	}
	ll cnt=0;
	for(int i=1;i<=n;i++)cnt+=!used[i];
	ll ans=1;
	ll mod=1000000007;
	for(int i=1;i<=cnt;i++)
		ans=(ans*26)%mod;
	cout<<ans<<endl;
	return 0;
}
