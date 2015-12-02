#include<iostream>
#include<cstring>
#include<queue>
#include<vector>
#include<algorithm>
#include<map>
#define MAX_N 100050
using namespace std;

vector<int> G[MAX_N];
int deep[MAX_N],siz[MAX_N];
int father[MAX_N];
int Heap[MAX_N],ind[MAX_N],pos[MAX_N],tot=0;

map<int,int> a[MAX_N];

void dfs(int u,int p){
	siz[u]=1;
	deep[u]=deep[p]+1;
	father[u]=p;
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(v==p)continue;
		dfs(v,u);
	}
}

void dfs2(int u,int p){
	ind[u]=++tot;
	pos[tot]=u;
	int maxSize=-1,maxNode;
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(v==p)continue;
		if(maxSize<siz[v])maxSize=siz[v],maxNode=v;
	}
	if(maxSize==-1)return;
	Heap[maxNode]=Heap[u];
	dfs2(maxNode,u);
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(v==p||v==maxNode)continue;
		Heap[v]=v;
		dfs2(v,u);
	}
}

void insertColor(int u,int v,int c){
	while(Heap[u]!=Heap[v]){
		if(deep[Heap[u]]<deep[Heap[v]])swap(u,v);
		a[ind[Heap[u]]][c]++;
		a[ind[u]+1][c]--;
		u=father[Heap[u]];
	}
	if(deep[u]<deep[v])swap(u,v);
	a[ind[v]][c]++;
	a[ind[u]+1][c]--;
}

#define lchild L,m,v<<1
#define rchild m+1,R,v<<1|1

struct node{
	int maxVal,maxInd;
	node(int i):maxVal(0),maxInd(i){}
	node(){}
	node operator=(node x){
		maxVal=x.maxVal;
		maxInd=x.maxInd;
		return *this;
	}
	bool operator<(const node &x)const{
		return maxVal<x.maxVal;
	}
};

int maxColor=MAX_N-10;

class SeqmentTree{
public:
	node tree[MAX_N*4];
	void pushUp(int v){
		tree[v]=max(tree[v<<1],tree[v<<1|1]);
	}
	void build(int L=1,int R=maxColor,int v=1){
		if(L==R){
			tree[v]=node(L);
			return;
		}
		int m=(L+R)>>1;
		build(lchild);
		build(rchild);
		pushUp(v);
	}
	void update(int i,int x,int L=1,int R=maxColor,int v=1){
		if(L==R){
			tree[v].maxVal+=x;
			return;
		}
		int m=(L+R)>>1;
		if(i<=m)update(i,x,lchild);
		if(i>m)update(i,x,rchild);
		pushUp(v);
	}
	node query(int a,int b,int L=1,int R=maxColor,int v=1){
		if(a<=L&&R<=b)
			return tree[v];
		int m=(L+R)>>1;
		node res(0);
		if(a<=m)res=max(res,query(a,b,lchild));
		if(b>m)res=max(res,query(a,b,rchild));
		return res;
	}
}seg;

int n,m;

int ans[MAX_N];

void init(){
	for(int i=1;i<=n;i++)G[i].clear();
	memset(deep,0,sizeof(deep));
	memset(siz,0,sizeof(siz));
	memset(Heap,0,sizeof(Heap));
	memset(father,0,sizeof(father));
	tot=0;
	memset(ind,0,sizeof(ind));
	memset(pos,0,sizeof(pos));
	memset(ans,0,sizeof(ans));
	seg.build();
	for(int i=0;i<MAX_N;i++)a[i].clear();
}

int main(){
	while(scanf("%d%d",&n,&m)==2){
		if(n==0&&m==0)break;
		init();
		for(int i=0;i<n-1;i++){
			int u,v;
			scanf("%d%d",&u,&v);
			G[u].push_back(v);
			G[v].push_back(u);
		}
		Heap[1]=1;
		dfs(1,0);
		dfs2(1,0);
		//for(int i=1;i<=n;i++)cout<<ind[i]<<" ";
		//cout<<endl;
		for(int i=0;i<m;i++){
			int u,v,c;
			scanf("%d%d%d",&u,&v,&c);
			insertColor(u,v,c);
		}
		//cout<<"----"<<endl;
		for(int i=1;i<=n;i++){
			for(map<int,int>::iterator it=a[i].begin();it!=a[i].end();it++){
		//		cout<<it->first<<" "<<it->second<<endl;
				seg.update(it->first,it->second);
			}
		//	for(int i=1;i<=8;i++)cout<<seg.tree[i].maxVal<<" ";
		//	cout<<endl;
			node now=seg.query(1,maxColor);
			if(now.maxVal==0)ans[pos[i]]=0;
			else ans[pos[i]]=now.maxInd;
		}
		//cout<<"----"<<endl;
		for(int i=1;i<=n;i++)printf("%d\n",ans[i]);
	}
	return 0;
}
