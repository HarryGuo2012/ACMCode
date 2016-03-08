#include<iostream>
#include<cstring>
#include<vector>
#include<set>
#include<algorithm>
#include<cstdio>
#define MAX_N 9
using namespace std;

typedef long long LL;

set<LL> se,se2;
const LL mod=1000000007;
const LL mod2=1000000009;

const LL P=3001;
const LL P2=3511;

bool G[MAX_N][MAX_N];

int dx[4]={1,0,-1,0},dy[4]={0,1,0,-1};
int dx2[4]={2,0,-2,0},dy2[4]={0,2,0,-2};

struct Node{
public:
	vector<pair<int,int> > v;
	void draw(){
		memset(G,0,sizeof(G));
		for(int i=0;i<v.size();i++)
			G[v[i].first][v[i].second]=1;
	}	
	LL Hash(){
		vector<pair<int,int> > vv=v;
		sort(vv.begin(),vv.end());
		LL res=0;
		for(int i=0;i<vv.size();i++){
			res=(res*P+vv[i].first)%mod;
			res=(res*P+vv[i].second)%mod;
		}
		return res;
	}
	LL Hash2(){
		vector<pair<int,int> > vv=v;
		sort(vv.begin(),vv.end());
		LL res=0;
		for(int i=0;i<vv.size();i++){
			res=(res*P2+vv[i].first)%mod2;
			res=(res*P2+vv[i].second)%mod2;
		}
		return res;
	}
};

Node S,T;

bool flag=false;
char cc;

void dfs(Node now,int step){
	if(flag)return;
	if(now.Hash()==T.Hash()&&now.Hash2()==T.Hash2()){
		flag=true;
		return;
	}
	if(step==8||(se.find(now.Hash())!=se.end()&&se2.find(now.Hash2())!=se2.end()))return;
	se.insert(now.Hash());
	se2.insert(now.Hash2());
	for(int i=0;i<now.v.size();i++){
		int x=now.v[i].first,y=now.v[i].second;
		Node tmp=now;
		for(int j=0;j<4;j++){
			now.draw();
			int nx=x+dx[j],ny=y+dy[j];
			if(nx>8||nx<=0||ny>8||ny<=0)continue;
			if(!G[nx][ny]){
				tmp.v[i].first=nx,tmp.v[i].second=ny;
				dfs(tmp,step+1);
				continue;
			}
			nx=x+dx2[j],ny=y+dy2[j];
			if(nx>8||nx<=0||ny>8||ny<=0||G[nx][ny])continue;
			tmp.v[i].first=nx,tmp.v[i].second=ny;
			dfs(tmp,step+1);
		}
	}
}

int main(){
	for(int i=0;i<4;i++){
		int a,b;
		cin>>a>>b;
		S.v.push_back(make_pair(a,b));
	}
	for(int i=0;i<4;i++){
		int a,b;
		cin>>a>>b;
		T.v.push_back(make_pair(a,b));
	}
	dfs(S,0);
	if(flag)
		cout<<"YES"<<endl;
	else
		cout<<"NO"<<endl;
	return 0;
}
