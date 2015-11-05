#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
#include<cstdio>
#include<queue>
#define MAX_N 200005
using namespace std;

int n,m;

typedef long long ll;

struct node{
	public:
		int x,y,z;//idx,val,tim
}a[MAX_N];

bool cmpx0(node u,node v){
	return u.x>v.x;
}

bool cmpx1(node u,node v){
	return u.x<v.x;
}

bool cmpy0(node u,node v){
	return u.y<v.y;
}

bool cmpy1(node u,node v){
	return u.y>v.y;
}

ll tree[MAX_N];
ll de[MAX_N];

void add(int i,ll x){
	while(i<MAX_N){
		tree[i]+=x;
		i+=i&(-i);
	}
}

ll query(int i){
	ll res=0;
	while(i){
		res+=tree[i];
		i-=i&(-i);
	}
	return res;
}

void Clear(int L,int R){
	for(int i=L;i<=R;i++){
		int t=a[i].z;
		while(t<MAX_N){
			tree[t]=0;
			t+=t&(-t);
		}
	}
}

void solve0(int L,int R){
	int m=(L+R)>>1;
	sort(a+L,a+m+1,cmpy0);
	sort(a+m+1,a+R+1,cmpy0);
	int j=L,cnt=0;
	for(int i=m+1;i<=R;i++){
		while(j<=m&&a[j].y<a[i].y)add(a[j++].z,1),cnt++;
		de[a[i].z]+=cnt-query(a[i].z-1);
	}
	Clear(L,m);
	sort(a+m+1,a+R+1,cmpx0);
}

void solve1(int L,int R){
	int m=(L+R)>>1;
	sort(a+L,a+m+1,cmpy1);
	sort(a+m+1,a+R+1,cmpy1);
	int j=L,cnt=0;
	for(int i=m+1;i<=R;i++){
		while(j<=m&&a[j].y>a[i].y)add(a[j++].z,1),cnt++;
		de[a[i].z]+=cnt-query(a[i].z-1);
	}
	Clear(L,m);
	sort(a+m+1,a+R+1,cmpx1);
}

void CDQ(int L,int R,int typ){
	if(L==R)return;
	int m=(L+R)>>1;
	CDQ(L,m,typ);
	if(typ)
		solve1(L,R);
	else
		solve0(L,R);
	CDQ(m+1,R,typ);
}

int pos[MAX_N];

int main(){
	while(scanf("%d%d",&n,&m)==2){
		memset(tree,0,sizeof(tree));
		memset(de,0,sizeof(de));
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i].y);
			a[i].x=i;
			pos[a[i].y]=i;
			a[i].z=m+1;
		}
		for(int i=1;i<=m;i++){
			int t;
			scanf("%d",&t);
			a[pos[t]].z=i;
		}
		sort(a+1,a+1+n,cmpx0);
		CDQ(1,n,0);
		sort(a+1,a+1+n,cmpx1);
		CDQ(1,n,1);
		sort(a+1,a+1+n,cmpx0);
		ll ans=0;
		/*for(int i=1;i<=m+1;i++)cout<<de[i]<<" ";
		cout<<endl;*/
		for(int i=1;i<=n;i++){
			ans+=query(a[i].y-1);
			add(a[i].y,1);
		}
		for(int i=1;i<=m;i++){
			printf("%lld\n",ans);
			ans-=de[i];
		}
	}
	return 0;
}
