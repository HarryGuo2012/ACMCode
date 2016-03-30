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

string s,t;
bool dp[5010][5010],dp2[5010][5010];

int main(void){
	int i,j;
	
	cin >> s >> t;
	int S = s.length();
	int T = t.length();
	
	for(i=S;i>=0;i--) for(j=T;j>=0;j--){
		if(i == S && j == T) dp[i][j] = true;
		if(i < S && j < T && s[i] == t[j]){
			if(dp[i+1][j+1]) dp[i][j] = true;
			if(j+1 < T && t[j] != t[j+1] && dp2[i+1][j+2]) dp[i][j] = true;
		}
		dp2[i][j] = dp2[i][j+1];
		if(dp[i][j]) dp2[i][j] = true;
	}
	
	cout << (dp[0][0] ? "Yes" : "No") << endl;
	
	return 0;
}
