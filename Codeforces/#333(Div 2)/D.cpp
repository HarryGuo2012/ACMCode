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
	cout<<"---"<<endl;
	for(int i=0;i<q;i++)cout<<L[i]<<" "<<R[i]<<endl;
	for(int i=0;i<n;i++)cout<<i<<" ";
	cout<<endl;
	for(int i=0;i<n;i++)cout<<b[i]<<" ";
	cout<<endl;
	for(int i=0;i<n;i++){
		int l=0,r=i-1;
		int x,y;
		while(l+1<r){
			int m=(l+r)>>1;
			if(RMQ(m,i-1)<b[i])
				r=m;
			else 
				l=m;
		}
		x=r;
		if(i==0||b[i-1]>b[i])x=i;
		l=i+1,r=n-1;
		while(l+1<r){
			int m=(l+r)>>1;
			if(RMQ(i+1,m)<=b[i])
				l=m;
			else
				r=m;
		}
		y=l;
		if(i==n-1||b[i+1]>b[i])y=i;
		if(y!=n-1&&b[y+1]==b[y])y=n-1;
		cout<<x<<" "<<y<<endl;
		for(int j=0;j<q;j++)
			if(L[j]<=i&&i<=R[j])
				ans[j]=ans[j]+(ll)(min(R[j],y)-i+1)*(i-max(L[j],x)+1)*b[i];
	}
	for(int i=0;i<q;i++)cout<<ans[i]<<endl;
	return 0;
}
