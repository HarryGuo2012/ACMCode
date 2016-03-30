#include <cstdio>
#include <queue>
#include <vector>
#include <cstring>
#define MAX_N 1000006

typedef pair<int,int> P;

int a[MAX_N],b[MAX_N];
int n,m;

int Hash(int i,int j){
	return i*n+j;
}

P Get(int x){
	return make_pair(x/n,x%n);
}

struct node{
	int val,pos;
	node(int vv,int pp):val(vv),pos(pp){}
	node(){}
};

bool cmp(node u,node v){
	return u.val<v.val;
}

std::vector<node> num;
std::queue<int> que;

void bfs(int s){
	que.push(s);
	vis[s]=1;
	b[s]=
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++){
			int h=Hash(i,j);
			scanf("%d",&a[h]);
			num.push_back(node(a[h],h));
		}
	std::sort(num.begin(),num.end(),cmp);
	for(auto u:num){
		if(vis[u.pos])continue;
		bfs(u.pos);
	}
	return 0;
}