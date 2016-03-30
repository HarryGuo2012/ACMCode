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

int N,K;
int ans[1000000][3];

void add(int x, int y, int z){
	ans[K][0] = x % N + 1;
	ans[K][1] = y % N + 1;
	ans[K][2] = z % N + 1;
	K++;
}

int main(void){
	int i,j;
	
	cin >> N;
	
	bool even = (N % 2 == 0);
	if(even) N--;
	
	for(i=1;2*i<N;i++) REP(j,N) add(j, j+i, j+2*i);
	
	if(even){
		for(i=2;2*i<N;i++) REP(j,N) add(j, j+i, j+2*i);
		N++;
		REP(i,N-1) add(N-1, i, (i+1)%(N-1));
		REP(i,N-1) add(N-1, i, (i+1)%(N-1));
		REP(i,N-1) add(N-1, i, (i+2)%(N-1));
	}
	
	cout << K << endl;
	REP(i,K) printf("%d %d %d\n", ans[i][0], ans[i][1], ans[i][2]);
	
	return 0;
}
