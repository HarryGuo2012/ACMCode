#include<iostream>
#include<cstring>
#include<string>
#include<vector>
#include<cstdio>
#include<queue>
#define MAX_N 100005
using namespace std;

typedef long long ll;
ll a[MAX_N];
ll w[MAX_N];
int n,k;
ll ans=1;

ll ten[10];

ll mod=1e9+7;

ll b[MAX_N];

int main(){
	ten[0]=1;
	for(int i=1;i<=9;i++)
		ten[i]=ten[i-1]*10;
	scanf("%d%d",&n,&k);
	int t=n/k;
	for(int i=0;i<t;i++)scanf("%I64d",&a[i]);
	for(int i=0;i<t;i++){
		scanf("%I64d",&b[i]);
		if(b[i]==0){
			if(k==1)w[i]=9/a[i];
			else
				w[i]=(ten[k]-1)/a[i]-(ten[k-1]-1)/a[i];
		}
		else
			w[i]=(ten[k]-1)/a[i]-(ten[k-1]*(b[i]+1)-1)/a[i]+(ten[k-1]*b[i]-1)/a[i];
	}
	for(int i=0;i<t;i++){
		if(b[i]!=0)
			ans=(ans*(w[i]+1))%mod;
		else 
			ans=(ans*w[i])%mod;
	}
	cout<<ans<<endl;
	return 0;
}
