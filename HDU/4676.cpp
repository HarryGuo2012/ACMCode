#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>
#include <cmath>
#define MAX_N 20004
using namespace std;

int bs;

int T;
int N,Q;

int a[MAX_N];
vector<int> d[MAX_N];

int prime[MAX_N],tot;
bool check[MAX_N];
int phi[MAX_N];

void Euler(){
	phi[1]=1;
	for(int i=2;i<MAX_N;i++){
		if(!check[i]){
			prime[tot++]=i;
			phi[i]=i-1;
		}
		for(int j=0;j<tot;j++){
			if(i*prime[j]>=MAX_N)break;
			check[i*prime[j]]=1;
			if(i%prime[j]==0){
				phi[i*prime[j]]=prime[j]*phi[i];
				break;
			}
			else
				phi[i*prime[j]]=(prime[j]-1)*phi[i];
		}
	}
}

struct Node{
	int l,r;
	int id;
	Node(int ll,int rr,int ii):l(ll),r(rr),id(ii){}
	Node(){}
}qu[MAX_N];

bool cmp(Node a,Node b){
	if(a.l/bs==b.l/bs)return a.r<b.r;
	return a.l<b.l;
}

typedef long long ll;

ll cnt[MAX_N];

ll add(int x){
	ll sum=0;
	for(int i=0;i<d[x].size();i++)
		sum+=(ll)phi[d[x][i]]*(cnt[d[x][i]]++);
	return sum;
}

ll del(int x){
	ll sum=0;
	for(int i=0;i<d[x].size();i++)
		sum+=(ll)phi[d[x][i]]*(--cnt[d[x][i]]);
	return sum;
}

int pl,pr;
ll sum=0;

void work(int i){
	if(i!=1){
		for(int L=pl;L<qu[i].l;L++)sum-=del(a[L]);
		for(int L=qu[i].l;L<pl;L++)sum+=add(a[L]);
		for(int R=pr+1;R<=qu[i].r;R++)sum+=add(a[R]);
		for(int R=qu[i].r+1;R<=pr;R++)sum-=del(a[R]);
	}
	else{
		sum=0;
		for(int j=qu[i].l;j<=qu[i].r;j++)
			sum+=add(a[j]);
	}
	pl=qu[i].l,pr=qu[i].r;
}

ll ans[MAX_N];

int main(){
	Euler();
	scanf("%d",&T);
	for(int i=1;i<MAX_N;i++)
		for(int j=i;j<MAX_N;j+=i)
			d[j].push_back(i);
	int cas=0;
	while(T--){
		memset(cnt,0,sizeof(cnt));
		scanf("%d",&N);
		for(int i=1;i<=N;i++)
			scanf("%d",&a[i]);
		scanf("%d",&Q);
		bs=sqrt(N)+2;
		for(int i=1;i<=Q;i++){
			int l,r;
			scanf("%d%d",&l,&r);
			qu[i]=Node(l,r,i);
		}
		sort(qu+1,qu+Q+1,cmp);
		for(int i=1;i<=Q;i++){
			work(i);
			ans[qu[i].id]=sum;
		}
		printf("Case #%d:\n",++cas);
		for(int i=1;i<=Q;i++)
			printf("%lld\n",ans[i]);
	}
	return 0;
}