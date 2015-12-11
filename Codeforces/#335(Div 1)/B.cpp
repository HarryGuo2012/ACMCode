#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
#include<queue>
#include<cstdio>
#define MAX_N 100005
using namespace std;

typedef long long ll;

struct node{
	int id;
	ll val;
	node(int i,ll v):id(i),val(v){}
	node(){}
};

bool cmp1(node a,node b){
	return a.val>b.val;
}

vector<node> T;
vector<node> NT;

struct ansNode{
	int u,v;
	ansNode(int uu,int vv):u(uu),v(vv){}
	ansNode(){}
}ans[MAX_N];
int n,m;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		ll t,a;
		scanf("%I64d%I64d",&t,&a);
		if(a)T.push_back(node(i,t));
		else NT.push_back(node(i,t));
	}
	sort(T.begin(),T.end(),cmp1);
	sort(NT.begin(),NT.end(),cmp1);
	int x=0,y=1;
	for(int i=0;i<NT.size();i++){
		while(x<T.size()&&T[x].val>NT[i].val){
			x++;
			y=x+1;
		}
		if(x>=T.size()||y>=T.size()){
			cout<<-1<<endl;
			return 0;
		}
		ans[NT[i].id]=ansNode(x+1,y+2);
		y++;
		if(y==T.size()){
			x++;
			y=x+1;
		}
	}
	for(int i=0;i<T.size();i++)ans[T[i].id]=ansNode(i+1,i+2);
	for(int i=1;i<=m;i++)
		printf("%d %d\n",ans[i].u,ans[i].v);
	return 0;
}
