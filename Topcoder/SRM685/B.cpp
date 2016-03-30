#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#define MAX_N 55
using namespace std;

struct edge{
	int to, id;
	edge(int t, int i) : to(t), id(i){}
	edge(){}
};

int tot = 0;

vector<edge> G[MAX_N];

bool vis[MAX_N*MAX_N];

int n;

bool used[MAX_N];

void dfs2(int u){
	if(used[u])return;
	used[u] = 1;
	for(auto e : G[u]){
		if(!vis[e.id]){
			dfs2(e.to);
		}
	}
}

bool flag = false;

void check(){
	dfs2(0);
	for(int i = 0; i < n; i++)
		if(!used[i])return;
	flag = true;
}

set<pair<int, long long> > se;

long long Hash(){
	long long res = 0;
	for(int i = 0; i < n; i++)
		res |= 1 << i;
	return res;
}

void dfs(int s){
	if(flag)return;
	long long tmp = Hash();
	if(se.find(make_pair(s, tmp)) != se.end())return;
	se.insert(make_pair(s, tmp));
	if(s == (1 << n) - 1)check();
	for(int u = 0; u < n; u++){
		if((s >> u & 1) == 0)continue;
		for(auto e : G[u]){
			int t = e.to, i = e.id;
			if(vis[i])continue;
			if(s >> t & 1)continue;
			vis[i] = 1;
			dfs(s | (1 << t));
			vis[i] = 0;
		}
	}
}

class FoxAirline2{
public:
	string isPossible(int N, vector <int> a, vector <int> b){
		n = N;
		for(int i = 0; i < a.size(); i++){
			G[a[i]].push_back(edge(b[i], tot));
			G[b[i]].push_back(edge(a[i], tot++));
		}
		for(int i = 0; i < n; i++){
			if(flag)break;
			memset(vis, 0, sizeof(vis));
			dfs(1 << i);
		}
		if(flag)return "Possible";
		else return "Impossible";
	}	
};

