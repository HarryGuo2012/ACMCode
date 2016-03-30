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

#define INF (1<<29)
#define MAX 100000

int a[210];
int dist[2][2*MAX];
queue <int> q;

int main(void){
	int N,Q,i,j;
	
	cin >> N;
	REP(i,N) cin >> a[i];
	
	REP(i,2) REP(j,2*MAX) dist[i][j] = INF;
	dist[0][MAX] = 0;
	q.push(0); q.push(MAX);
	
	while(!q.empty()){
		int t = q.front(); q.pop();
		int c = q.front(); q.pop();
		
		REP(i,N){
			int c2 = 2 * a[i] - (c - MAX) + MAX;
			if(c2 >= 0 && c2 < 2 * MAX && dist[t^1][c2] == INF){
				dist[t^1][c2] = dist[t][c] + 1;
				q.push(t^1);
				q.push(c2);
			}
		}
	}
	
	cin >> Q;
	REP(i,Q){
		int s,t;
		scanf("%d%d", &s, &t);
		int ans = min(dist[0][t-s+MAX], dist[1][t+s+MAX]);
		if(ans == INF) ans = -1;
		printf("%d\n", ans);
	}
	
	return 0;
}
