#include<stdio.h>
#include<string.h>
#include<vector>
#include<algorithm>
#include<queue>

const int MAXN = 10000;
const int MAXNODE = MAXN * 2 + 2;

struct edge{
	int t,u;
	edge *nxt,*op;
	void init(const int &s,const int &t,const int &u,edge* const &op);
}*V[MAXNODE + 10], *FV[MAXNODE + 10], E[MAXNODE * 10], *PE = E;

void edge::init(const int &s,const int &t,const int &u,edge* const &op){
	this -> t = t;
	this -> u = u;
	this -> op = op;
	this -> nxt = V[s];
	V[s] = this;
}

inline void addedge(const int &s, const int &t, const int &u){
	PE->init(s, t, u, PE + 1), ++PE;
	PE->init(t, s, 0, PE - 1), ++PE;
}

int dist[MAXNODE + 10];
int Q[MAXNODE + 10], QT, QH;
bool gapFlag;
int cntDist[MAXNODE + 10];
int S, T;

inline bool modlabel(){
	for(int i = 0; i <= T; ++i){
		FV[i] = V[i];
		cntDist[i] = 0;
		dist[i] = T + 1;
	}
	dist[T] = 0;
	QT = QH = -1;
	Q[++QT] = T;
	while(QH++ != QT){
		int x = Q[QH];
		int ndist = dist[x] + 1;
		for(edge *ii = V[x]; ii; ii = ii -> nxt) if(ii -> op -> u && dist[ii -> t] > ndist){
			dist[ii -> t] = ndist;
			++cntDist[ndist];
			Q[++QT] = ii -> t;
		}
	}
	gapFlag = false;
	return dist[S] != T + 1;
}

int aug(int x, int limit){
	if(x == T) return limit;
	int kk, ll = limit;
	for(; FV[x]; FV[x] = FV[x] -> nxt) if(FV[x] -> u && dist[FV[x]->t] + 1 == dist[x]){
		kk = aug(FV[x] -> t, std::min(ll, FV[x] -> u));
		FV[x] -> u -= kk, FV[x] -> op -> u += kk;
		ll -= kk;
		if(!ll || gapFlag) return limit - ll;
	}
	if(--cntDist[dist[x]] == 0){
		gapFlag = true;
	}
	dist[x] = T + 1;
	return limit - ll;
}

int N;

int maxflow;

int mark[MAXN + 10];
std::priority_queue<std::pair<int, int> > preQ[MAXN + 10];
std::vector<int> treeEdge[MAXN + 10];
bool vis[MAXN + 10];
bool decided[MAXN + 10];
std::vector<int> toDecide[MAXN + 10];
int ans[MAXN + 10];

int depth[MAXN + 10];
int fa[MAXN + 10];
int preDecide;

void getMark(int x, int label){
	mark[x] = label;
	vis[x] = 1;
	for(int i = 0; i < int(treeEdge[x].size()); ++i) if(!vis[treeEdge[x][i]]){
		depth[treeEdge[x][i]] = depth[x] + 1;
		fa[treeEdge[x][i]] = x;
		getMark(treeEdge[x][i], label);
	}
}

inline void getMark(){
	memset(vis, 0, sizeof(vis));
	vis[1] = 1;
	depth[1] = 0;
	for(int i = 0; i < int(treeEdge[1].size()); ++i){
		depth[treeEdge[1][i]] = 1;
		fa[treeEdge[1][i]] = 1;
		getMark(treeEdge[1][i], treeEdge[1][i]);
	}
}

bool getPreDecide(int x){
	vis[x] = 1;
	for(int i = 0; i < int(treeEdge[x].size()); ++i) if(!vis[treeEdge[x][i]]){
		if(!getPreDecide(treeEdge[x][i])) return false;;
		if(preQ[treeEdge[x][i]].size() > preQ[x].size()){
			std::swap(preQ[treeEdge[x][i]], preQ[x]);
		}
		while(preQ[treeEdge[x][i]].size()){
			preQ[x].push(preQ[treeEdge[x][i]].top());
			preQ[treeEdge[x][i]].pop();
		}
	}
	if(preQ[x].size()){
		if(preQ[x].top().first > depth[x]){
			return false;
		}
		else{
			ans[preQ[x].top().second] = x;
			decided[x] = true;
			++preDecide;
			preQ[x].pop();
		}
	}
	return true;
}

void getAnswer(int x){
	vis[x] = 1;
	for(int i = 0; i < int(treeEdge[x].size()); ++i) if(!vis[treeEdge[x][i]]){
		getAnswer(treeEdge[x][i]);
		if(toDecide[treeEdge[x][i]].size() > toDecide[x].size()){
			std::swap(toDecide[treeEdge[x][i]], toDecide[x]);
		}
		while(toDecide[treeEdge[x][i]].size()){
			toDecide[x].push_back(toDecide[treeEdge[x][i]].back());
			toDecide[treeEdge[x][i]].pop_back();
		}
	}
	if(!decided[x]){
		ans[toDecide[x].back()] = x;
		toDecide[x].pop_back();
	}
}

int main(){
	scanf("%d", &N);
	S = 0, T = 2 * N + 1;
	for(int i = 1; i < N; ++i){
		int x, y;
		scanf("%d%d", &x, &y);
		treeEdge[x].push_back(y);
		treeEdge[y].push_back(x);
	}
	
	getMark();
	for(int i = N; i > 1; --i){
		addedge(i, fa[i], T);
	}
	std::vector<std::pair<int, std::pair<int, int> > > rems;
	for(int i = 1; i <= N; ++i){
		int x, y;
		scanf("%d%d", &x, &y);
		if(depth[x] > depth[y]) std::swap(x, y);
		if(x == 1 || mark[x] == mark[y]){
			preQ[y].push(std::make_pair(depth[x], i));
		}
		else{
			addedge(S, N + i, 1);
			addedge(N + i, x, 1);
			addedge(N + i, y, 1);
			rems.push_back(std::make_pair(i, std::make_pair(x, y)));
		}
	}
	
	memset(vis, 0, sizeof(vis));
	if(!getPreDecide(1) || preQ[1].size()){
		printf("No\n");
		return 0;
	}
	for(int i = 1; i <= N; ++i){
		if(!decided[i]){
			addedge(i, T, 1);
		}
	}
	
	maxflow = 0;
	while(modlabel()){
		maxflow += aug(S, T);
	}
	if(maxflow != N - preDecide){
		printf("No\n");
		return 0;
	}
	for(int i = 1; i <= N; ++i){
		for(edge *ii = V[N + i]; ii; ii = ii -> nxt){
			if(ii -> u == 0 && ii -> t > 0 && ii -> t <= N){
				toDecide[ii -> t].push_back(i);
			}
		}
	}
	
	memset(vis, 0, sizeof(vis));
	getAnswer(1);
	
	printf("Yes\n");
	for(int i = 1; i <= N; ++i){
		printf("%d%c", ans[i], i == N ? '\n' : ' ');
	}
	
	return 0;
}
