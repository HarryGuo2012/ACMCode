#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#include <cstdio>
#define MAX_N 1003
#define MAX_M 5003
using namespace std;

int n,m;

struct US{

	int father[MAX_N];

	void init(){
		for(int i=0;i<=n;i++)father[i]=i;
	}

	int Find(int x){
		if(x==father[x])return x;
		return father[x]=Find(father[x]);
	}

	bool Same(int x,int y){
		return Find(x)==Find(y);
	}

	void unionSet(int x,int y){
		int u=Find(x),v=Find(y);
		if(u==v)return;
		father[u]=v;
	}
};

struct OP{
	int u,v;
	int id;
	OP(int uu,int vv,int ii):u(uu),v(vv),id(ii){}
	OP(){}
};

US us;

vector<OP> vo;
int T;

US us0;

int main(){
	scanf("%d",&T);
	while(T--){
		int last=0;
		vo.clear();
		scanf("%d%d",&n,&m);
		int cnt=n;
		us0.init();
		for(int i=1;i<=m;i++){
			int o,u,v;
			scanf("%d%d%d",&o,&u,&v);
			u=u^last,v=v^last;
			if(o){
				int ans=0;
				us.init();
				for(int j=0;j<vo.size();j++){
					us.unionSet(vo[j].u,vo[j].v);
					if(us.Same(u,v)){
						ans=vo[j].id;
						break;
					}
				}
				last=ans;
				printf("%d\n",ans);
			}
			else{
				vo.push_back(OP(u,v,i));
				if(!us0.Same(u,v)){
					us0.unionSet(u,v);
					cnt--;
				}
				printf("%d\n",cnt);
				last=cnt;
			}
		}
	}
	return 0;
}