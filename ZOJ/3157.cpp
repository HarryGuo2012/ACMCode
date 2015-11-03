#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
#include<map>
#include<cstdio>
#define MAX_N 10004
using namespace std;

int n;
const double eps=1e-8;

struct node{
	public:
		double u,v;
}a[MAX_N];

double x[MAX_N][2],y[MAX_N][2];

double cross(int i,double t){
	double k=y[i][0]-y[i][1];
	k/=x[i][0]-x[i][1];
	double b=-k*x[i][0]+y[i][0];
	return k*t+b;
}

bool cmp(node i,node j){
	return i.u<j.u;
}

double tmp[MAX_N];
int b[MAX_N];

int tree[MAX_N];

int query(int x){
	int res=0;
	while(x)res+=tree[x],x-=x&(-x);
	return res;
}

void add(int i,int x){
	while(i<=n)tree[i]+=x,i+=i&(-i);
}

int main(){
	while(scanf("%d",&n)==1){
		memset(tree,0,sizeof(tree));
		for(int i=1;i<=n;i++)
			scanf("%lf%lf%lf%lf",&x[i][0],&y[i][0],&x[i][1],&y[i][1]);
		
		double L,R;
		scanf("%lf%lf",&L,&R);
		L+=eps;
		R-=eps;
		for(int i=1;i<=n;i++){
			a[i].u=cross(i,L);
			a[i].v=cross(i,R);	
		}
		sort(a+1,a+1+n,cmp);
		for(int i=1;i<=n;i++)tmp[i]=a[i].v;
		sort(tmp+1,tmp+1+n);
		int tot=unique(tmp+1,tmp+1+n)-tmp-1;
		for(int i=1;i<=n;i++)
			b[i]=lower_bound(tmp+1,tmp+1+tot,a[i].v)-tmp;
		//for(int i=1;i<=n;i++)cout<<b[i]<<" ";
		//cout<<endl;
		int ans=0;
		for(int i=1;i<=n;i++){
			ans+=query(b[i]);
			add(b[i],1);
		}
		printf("%d\n",n*(n-1)/2-ans);
	}
	return 0;
}
