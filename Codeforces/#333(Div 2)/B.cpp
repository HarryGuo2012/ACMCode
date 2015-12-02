#include<iostream>
#include<cstring>
#include<queue>
#include<vector>
#include<cstdio>
#include<cmath>
#define MAX_N 100005
#define MAX_S 25
using namespace std;

int a[MAX_N];

struct node{
	int val,pos;
	friend bool operator<(node x,node y){
		return x.val<y.val;
	}
	friend bool operator>(node x,node y){
		return x.val>y.val;
	}
	node operator=(node x){
		val=x.val;
		pos=x.pos;
		return *this;
	}
	node(int v,int p):val(v),pos(p){}
	node(){}
};

node stMax[MAX_N][MAX_S],stMin[MAX_N][MAX_S];

int n;

void init(){
	for(int i=0;i<n;i++)stMin[i][0]=stMax[i][0]=node(a[i],i);
	for(int j=1;(1<<j)<=n;j++)
		for(int i=0;i+(1<<(j-1))<n;i++){
			stMin[i][j]=min(stMin[i][j-1],stMin[i+(1<<(j-1))][j-1]);
			stMax[i][j]=max(stMax[i][j-1],stMax[i+(1<<(j-1))][j-1]);
		}
}

node queryMin(int u,int v){
	int k=(int)(log(v-u+1.0)/log(2.0));
	return min(stMin[u][k],stMin[v-(1<<k)+1][k]);
}

node queryMax(int u,int v){
	int k=(int)(log(v-u+1.0)/log(2.0));
	return max(stMax[u][k],stMax[v-(1<<k)+1][k]);
}

int main(){
	cin.sync_with_stdio(false);
	cin>>n;
	for(int i=0;i<n;i++)cin>>a[i];
	init();
	int i=0,j=0;
	int ans=0;
	char cc;
	while(i<n){
		node mi=queryMin(j,i),ma=queryMax(j,i);
		//cout<<i<<" "<<j<<" "<<mi.val<<" "<<ma.val<<endl;
		//cin>>cc;
		if(mi.val<=a[i]-2)j=mi.pos+1;
		else if(ma.val>=a[i]+2)j=ma.pos+1;
		else{
			ans=max(ans,i-j+1);
			i++;	
		}
	}
	cout<<ans<<endl;
	return 0;
}
