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
#define MOD 1000000007ll

ll N;
int K;
ll a[10];

int sz;
vector <ll> v;

int b[10];
int c[10];

ll comb(ll N, int K){
	int i;
	ll ans = 1;
	if(K < 0 || K > N) return 0;
	REP(i,K){
		ans = ans * (N - i) % MOD;
		while(ans % (i + 1) != 0) ans += MOD;
		ans /= (i + 1);
	}
	return ans;
}

bool matching(int B, int pos){
	int i,j;
	
	if(pos == K){
		REP(i,B){
			ll sum = 0;
			REP(j,K) if(c[j] == i) sum += a[j];
			if(sum < v[b[i]]) return false;
		}
		return true;
	}
	
	REP(i,B) if(v[b[i]] >= a[pos]){
		c[pos] = i;
		if(matching(B, pos+1)) return true;
	}
	
	return false;
}

ll func(int B){
	ll ans = 0;
	int mask,i;
	
	REP(mask,(1<<B)){
		ll minsum = B - 1;
		REP(i,B) if(mask&(1<<i)) minsum += v[b[i]+1]; else minsum += v[b[i]];
		if(minsum <= N){
			ll tmp = comb(N - minsum + 2 * B, 2 * B);
			if(__builtin_popcount(mask) % 2 == 0){
				ans = (ans + tmp) % MOD;
			} else {
				ans = (ans - tmp + MOD) % MOD;
			}
		}
	}
	
	return ans;
}

ll dfs(int pos){
	ll ans = 0;
	if(pos >= 1 && matching(pos, 0)) ans = func(pos);
	
	if(pos < K){
		int i;
		REP(i,sz-1){
			b[pos] = i;
			ll tmp = dfs(pos+1);
			ans = (ans + tmp) % MOD;
		}
	}
	
	return ans;
}

int main(void){
	int i,j,mask;
	
	cin >> N >> K;
	REP(i,K) cin >> a[i];
	
	REP(mask,(1<<K)) if(mask != 0){
		ll sum = 0;
		REP(i,K) if(mask&(1<<i)) sum += a[i];
		v.push_back(sum + 1);
	}
	REP(i,K) v.push_back(a[i]);
	
	sort(v.begin(),v.end());
	sz = v.size();
	
	ll ans = dfs(0);
	cout << ans << endl;
	
	return 0;
}
