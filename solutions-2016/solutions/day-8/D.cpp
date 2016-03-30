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

#define MOD 1000000007

int p[2010],q[2010];
int invp[2010],invq[2010];
int dp[4010][2010][4]; // len, last, mask

int main(void){
	int N,i,j,k,l,mask;
	
	cin >> N;
	REP(i,N) cin >> p[i];
	REP(i,N) cin >> q[i];
	
	REP(i,N){
		p[i]--; q[i]--;
		invp[p[i]] = i;
		invq[q[i]] = i;
	}
	
	dp[0][0][3] = 1;
	vector <pair <int, int> > v,w;
	
	REP(i,2*N) REP(j,N) for(mask=1;mask<=3;mask++) if(dp[i][j][mask] != 0){
		w.clear();
		
		if(i == 0){
			w.push_back(make_pair(p[0], 1));
			w.push_back(make_pair(q[0], 2));
		} else {
			if(mask&1){
				int L = invp[j] + 1, R = i - invp[j] - 1;
				if(L != N) w.push_back(make_pair(p[L], 1));
				if(R != N) w.push_back(make_pair(q[R], 2));
			}
			if(mask&2){
				int L = i - invq[j] - 1, R = invq[j] + 1;
				if(L != N) w.push_back(make_pair(p[L], 1));
				if(R != N) w.push_back(make_pair(q[R], 2));
			}
		}
		
		sort(w.begin(),w.end());
		
		k = 0;
		while(k < w.size()){
			int i2 = i + 1;
			int j2 = w[k].first;
			int mask2 = 0;
			for(l=k;l<w.size();l++){
				if(w[l].first != w[k].first) break;
				mask2 |= w[l].second;
			}
			dp[i2][j2][mask2] = (dp[i2][j2][mask2] + dp[i][j][mask]) % MOD;
			k = l;
		}
	}
	
	int ans = 0;
	REP(i,N) REP(j,4) ans = (ans + dp[2*N][i][j]) % MOD;
	cout << ans << endl;
	
	return 0;
}
