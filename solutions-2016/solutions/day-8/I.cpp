#include <string.h>
#if ( _WIN32 || __WIN32__ || _WIN64 || __WIN64__ )
#define INT64 "%I64d"
#else
#define INT64 "%lld"
#endif

#if ( _WIN32 || __WIN32__ || _WIN64 || __WIN64__ )
#define UNS64 "%I64u"
#else
#define UNS64 "%llu"
#endif
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <algorithm>
#include <functional>
#include <utility>
#include <bitset>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstdio>

using namespace std;

#define REP(i,n) for((i)=0;(i)<(int)(n);(i)++)
#define snuke(c,itr) for(__typeof((c).begin()) itr=(c).begin();itr!=(c).end();itr++)

typedef long long ll;
#define INF (1ll<<60)

string ds = "UDLR";
int dx[] = {0,0,-1,1}, dy[] = {1,-1,0,0};

int N;
int x[100010],y[100010],d[100010];

map <int, vector <pair <int, int> > > mx,my;
int next[100010][4];

ll dist[100010][4];
bool used[100010][4];
priority_queue <pair <ll, pair <int, int> > > q;

void add(int v, int dv, ll d){
	if(d < dist[v][dv]){
		dist[v][dv] = d;
		q.push(make_pair(-d, make_pair(v, dv)));
	}
}

void func(void){
	int i,j;
	
	REP(i,N) REP(j,4) dist[i][j] = INF;
	dist[0][d[0]] = 0;
	q.push(make_pair(0ll, make_pair(0, d[0])));
	
	while(!q.empty()){
		ll dis = -q.top().first;
		int v = q.top().second.first, dv = q.top().second.second;
		q.pop();
		
		if(used[v][dv]) continue;
		used[v][dv] = true;
		
		add(v, d[v], dis);
		if(next[v][dv] != -1){
			int u = next[v][dv];
			add(u, dv, dis + abs(x[u] - x[v]) + abs(y[u] - y[v]));
		}
	}
}

int main(void){
	int i,j;
	ll T;
	
	cin >> N >> T;
	REP(i,N){
		char ch;
		scanf(" %d %d %c ", &x[i], &y[i], &ch);
		REP(j,4) if(ds[j] == ch) d[i] = j;
	}
	
	REP(i,N) REP(j,4) next[i][j] = -1;
	
	REP(i,N){
		mx[x[i]].push_back(make_pair(y[i], i));
		my[y[i]].push_back(make_pair(x[i], i));
	}
	
	snuke(mx,itr){
		vector <pair <int, int> > v = (itr->second);
		sort(v.begin(),v.end());
		int sz = v.size();
		REP(i,sz-1){
			int p = v[i].second;
			int q = v[i+1].second;
			next[p][0] = q;
			next[q][1] = p;
		}
	}
	
	snuke(my,itr){
		vector <pair <int, int> > v = (itr->second);
		sort(v.begin(),v.end());
		int sz = v.size();
		REP(i,sz-1){
			int p = v[i].second;
			int q = v[i+1].second;
			next[p][3] = q;
			next[q][2] = p;
		}
	}
	
	func();
	
	REP(i,N){
		ll t = 0;
		if(dist[i][d[i]] < T) t = T - dist[i][d[i]];
		printf(INT64 " " INT64 "\n", x[i] + dx[d[i]] * t, y[i] + dy[d[i]] * t);
	}
	
	return 0;
}
