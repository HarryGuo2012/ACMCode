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
ll MOD;

ll comb[5010][5010];
ll dp[5010],dp2[5010];
ll power[5010];

int main(void){
	int N,i,j;
	
	cin >> N >> MOD;
	
	REP(i,N+1) REP(j,i+1){
		if(j == 0 || j == i) comb[i][j] = 1;
		else comb[i][j] = (comb[i-1][j-1] + comb[i-1][j]) % MOD;
	}
	
	power[0] = 1;
	for(i=1;i<=N;i++) power[i] = power[i-1] * 4 % MOD;
	
	REP(i,N+1) REP(j,N+1) if(2*(i+j) <= N) dp[2*(i+j)] = (dp[2*(i+j)] + comb[2*i+2*j][i] * comb[i+2*j][i] % MOD * comb[2*j][j]) % MOD;
	
	REP(i,N+1){
		dp2[i] = dp[i];
		for(j=1;j<i;j++) dp2[i] = (dp2[i] - dp2[j] * dp[i-j] % MOD + MOD) % MOD;
	}
	
	ll ans = (N + 1) * power[N] % MOD;
	for(i=1;i<=N;i++) ans = (ans - dp2[i] * power[N-i] % MOD * (N-i+1) % MOD + MOD) % MOD;
	
	cout << ans << endl;
	
	return 0;
}
