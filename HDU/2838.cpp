#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#define MAX_N 100005
using namespace std;

long long ans=0;

struct node{
	public:
		int x,y;
}a[MAX_N];

bool cmpx(node u,node v){
	return u.x<v.x;
}

bool cmpy(node u,node v){
	return u.y>v.y;
}

int n;

void solve(int L,int R){
	int m=(L+R)>>1;
	sort(a+L,a+m+1,cmpy);
	sort(a+m+1,a+R+1,cmpy);
	int j=L;
	long long sum=0;
	long long cnt=0;
	for(int i=m+1;i<=R;i++){
		while(j<=m&&a[j].y>a[i].y)sum=sum+a[j++].y,cnt++;
		if(cnt)
			ans+=sum+a[i].y*cnt;
	}
	sort(a+m+1,a+R+1,cmpx);
}

void CDQ(int L,int R){
	if(L==R)return;
	int m=(L+R)>>1;
	CDQ(L,m);
	solve(L,R);
	CDQ(m+1,R);
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i].y);
		a[i].x=i;
	}
	CDQ(1,n);
	cout<<ans<<endl;
	return 0;
}
