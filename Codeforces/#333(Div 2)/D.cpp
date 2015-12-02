#include<iostream>
#include<cstring>
#include<vector>
#include<cstdio>
#include<queue>
#include<algorithm>
#include<cmath>
#define MAX_N 100005
#define MAX_Q 233
#define MAX_S 25
using namespace std;

int n,q;
int a[MAX_N],b[MAX_N];
int st[MAX_N][MAX_S];

int L[MAX_Q],R[MAX_Q];
typedef long long ll;
ll ans[MAX_Q];

void init(){
	for(int i=0;i<n;i++)st[i][0]=b[i];
	for(int j=1;(1<<j)<=n;j++)
		for(int i=0;i+(1<<(j-1))<n;i++)
			st[i][j]=max(st[i][j-1],st[i+(1<<(j-1))][j-1]);
}

int RMQ(int l,int r){
	int k=(int)(log(r-l+1.0)/log(2.0));
	return max(st[l][k],st[r-(1<<k)+1][k]);
}

int main(){
	cin.sync_with_stdio(false);
	cin>>n>>q;
	for(int i=0;i<n;i++)cin>>a[i];
	n--;
	for(int i=0;i<n;i++)b[i]=abs(a[i]-a[i+1]);
	for(int i=0;i<q;i++){
		cin>>L[i]>>R[i];
		R[i]-=2;L[i]--;
	}
	init();
	/*
	cout<<"---"<<endl;
	for(int i=0;i<q;i++)cout<<L[i]<<" "<<R[i]<<endl;
	for(int i=0;i<n;i++)cout<<i<<" ";
	cout<<endl;
	for(int i=0;i<n;i++)cout<<b[i]<<" ";
	cout<<endl;
	*/
	for(int i=0;i<n;i++){
		int x,y;
		int l=-1,r=i-1;
		while(r-l>1){
			int mid=(r+l)>>1;
			if(RMQ(mid,i-1)<=b[i])r=mid;
			else l=mid;
		}
		x=r;
		if(i==0||b[i]<b[i-1])x=i;
		l=i+1,r=n;
		while(r-l>1){
			int mid=(r+l)>>1;
			if(RMQ(i+1,mid)<b[i])l=mid;
			else r=mid;
		}
		y=l;
		if(i==n-1||b[i]<=b[i+1])y=i;
		//cout<<x<<" "<<y<<endl;
		for(int j=0;j<q;j++)
			if(L[j]<=i&&i<=R[j])
				ans[j]=ans[j]+(ll)(min(R[j],y)-i+1)*(i-max(L[j],x)+1)*b[i];
	}
	for(int i=0;i<q;i++)cout<<ans[i]<<endl;
	return 0;
}
