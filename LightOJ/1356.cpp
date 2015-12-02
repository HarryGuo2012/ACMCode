#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<queue>
#include<cstring>
#define MAX_A 500005
#define MAX_N 40004
#define MAX_V MAX_N
#define INF 1008611
using namespace std;

struct edge{int to,cap,rev;bool isRev;};

vector<edge> G[MAX_N];
int level[MAX_V];
int iter[MAX_V];

void add_edge(int from,int to,int cap) {
    G[from].push_back((edge) {to, cap, G[to].size(),0});
    G[to].push_back((edge) {from, 0, G[from].size() - 1,1});
}

void bfs(int s) {
    memset(level, -1, sizeof(level));
    queue<int> que;
    level[s] = 0;
    que.push(s);
    while (!que.empty()) {
        int v = que.front();
        que.pop();
        for (int i = 0; i < G[v].size(); i++) {
            edge &e = G[v][i];
            if (e.cap > 0 && level[e.to] < 0) {
                level[e.to] = level[v] + 1;
                que.push(e.to);
            }
        }
    }
}

int dfs(int v,int t,int f) {
    if (v == t)return f;
    for (int &i = iter[v]; i < G[v].size(); i++) {
        edge &e = G[v][i];
        if (e.cap > 0 && level[v] < level[e.to]) {
            int d = dfs(e.to, t, min(f, e.cap));
            if (d > 0) {
                e.cap -= d;
                G[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

int max_flow(int s,int t) {
    int flow = 0;
    for (; ;) {
        bfs(s);
        if (level[t] < 0)return flow;
        memset(iter, 0, sizeof(iter));
        int f;
        while ((f = dfs(s, t, INF)) > 0) {
            flow += f;
        }
    }
}


bool isPrime[MAX_A];
int prime[MAX_A],tot=0;

void getPrime(){
	memset(isPrime,1,sizeof(isPrime));
	for(int i=2;i<MAX_A;i++)
		if(isPrime[i]){
			for(int j=2*i;j<MAX_A;j+=i)isPrime[j]=0;
			prime[tot++]=i;
	}
}

int Te,n,a[MAX_N];
vector<int> odd,even;

int cas=0;

int S=MAX_N-1;
int T=MAX_N-2;

void init(){
	odd.clear();
	even.clear();
	memset(iter,0,sizeof(iter));
	for(int i=0;i<MAX_N;i++)G[i].clear();
}

int div(int x){
	int i=0,cnt=0;
	while(x>1){
		if(x%prime[i])i++;
		else x/=prime[i],cnt++;
	}	
	return cnt;
}

int main(){
	getPrime();
	scanf("%d",&Te);
	while(Te--){
		scanf("%d",&n);
		init();
		for(int i=0;i<n;i++)scanf("%d",&a[i]);
		for(int i=0;i<n;i++){
			if(div(a[i])&1){
				odd.push_back(i);
				add_edge(S,i+1,1);
				//cout<<'S'<<" "<<a[i]<<endl;
			}
			else {
				even.push_back(i);
				add_edge(i+1,T,1);
				//cout<<a[i]<<" T"<<endl;
			}
		}
		for(int i=0;i<odd.size();i++)
			for(int j=0;j<even.size();j++){
				int u=a[odd[i]],v=a[even[j]];
				if(u>v)swap(u,v);
				if(v%u==0&&isPrime[v/u])add_edge(odd[i]+1,even[j]+1,1);
				//cout<<a[odd[i]]<<" "<<a[even[j]]<<endl;
			}
		printf("Case %d: %d\n",++cas,n-max_flow(S,T));
	}
	return 0;
}
