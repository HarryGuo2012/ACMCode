#include <string.h>
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

#define MAXV 100010

int parent[MAXV],rank[MAXV];

void init(int n){
	int i;
	REP(i,n) {parent[i] = i; rank[i] = 1;}
}

int root(int x){
	if(parent[x] != x) parent[x] = root(parent[x]);
	return parent[x];
}

void connect(int x, int y){
	int rx=root(x),ry=root(y);
	if(rx == ry) return;
	if(rank[rx] > rank[ry]) {parent[ry] = rx; rank[rx] += rank[ry];}
	if(rank[rx] <= rank[ry]) {parent[rx] = ry; rank[ry] += rank[rx];}
}

int N;
int x[100010],y[100010];
vector <pair <int, int> > s,t; // coordinate, id

bool check(ll D){
	int i;
	
	init(N);
	REP(i,N){
		if(s[i].first - s[0].first >= D) connect(s[0].second, s[i].second);
		if(s[N-1].first - s[i].first >= D) connect(s[N-1].second, s[i].second);
		if(t[i].first - t[0].first >= D) connect(t[0].second, t[i].second);
		if(t[N-1].first - t[i].first >= D) connect(t[N-1].second, t[i].second);
	}
	
	REP(i,N) if(root(i) != root(0)) return false;
	return true;
}

int main(void){
	int i;
	
	cin >> N;
	REP(i,N) scanf("%d%d", &x[i], &y[i]);
	
	REP(i,N){
		s.push_back(make_pair(x[i] + y[i], i));
		t.push_back(make_pair(x[i] - y[i], i));
	}
	sort(s.begin(),s.end());
	sort(t.begin(),t.end());
	
	ll low = 0, high = (1ll<<31);
	while(high - low > 1){
		ll mid = (low + high) / 2;
		if(check(mid)) low = mid; else high = mid;
	}
	
	cout << low << endl;
	
	return 0;
}
