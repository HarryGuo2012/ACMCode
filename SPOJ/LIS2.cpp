#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<map>
#include<vector>
#define MAX_N 100050
using namespace std;

int N;   

struct node{
	int x,y,z;
}a[MAX_N];

bool cmpx(node u,node v){
	return u.x<v.x;
}

bool cmpy(node u,node v){
	return u.y<v.y;
}

bool cmpz(node u,node v){
	return u.z<v.z;
}

int dp[MAX_N];

int tree[MAX_N];
int treeSize;

void update(int i,int x){
	while(i<=treeSize){
		tree[i]=max(tree[i],x);
		i+=i&(-i);
	}
}

void init(int i){
	while(i<=treeSize){
		tree[i]=0;
		i+=i&(-i);
	}
}

int query(int i){
	int res=0;
	while(i){
		res=max(res,tree[i]);
		i-=i&(-i);
	}
	return res;
}

void solve(int L,int R){
	int m=(L+R)>>1;
	sort(a+L,a+m+1,cmpy);
	sort(a+m+1,a+R+1,cmpy);
	int j=L;
	for(int i=m+1;i<=R;i++){
		for(;j<=m&&a[j].y<a[i].y;j++)
			update(a[j].z,dp[a[j].x]);
		int tmp=query(a[i].z-1)+1;
		dp[a[i].x]=max(dp[a[i].x],tmp);
	}
	for(int i=L;i<=m;i++)init(a[i].z);
	sort(a+m+1,a+R+1,cmpx);
}

void CDQ(int L,int R){
	if(L==R)return;
	int m=(L+R)>>1;
	CDQ(L,m);
	solve(L,R);
	CDQ(m+1,R);
}

vector<int> v;

int main(){
	scanf("%d",&N);
	for(int i=1;i<=N;i++){
		scanf("%d%d",&a[i].y,&a[i].z);
		v.push_back(a[i].z);
		a[i].x=i;
		dp[i]=1;
	}
	sort(v.begin(),v.end());
	for(int i=1;i<=N;i++)
		a[i].z=lower_bound(v.begin(),v.end(),a[i].z)-v.begin()+1;
	treeSize=N+2;
	CDQ(1,N);
	int ans=0;
	for(int i=1;i<=N;i++)ans=max(ans,dp[i]);
	printf("%d\n",ans);
	return 0;
}