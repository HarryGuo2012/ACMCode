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

int main(void){
	int N,a=0,b=0,c=0,i;
	
	cin >> N;
	REP(i,N){
		int x;
		scanf("%d", &x);
		if(x == 1) a++; else if(x == 2) b++; else c++;
	}
	
	ll ans = 0;
	if(a - c == 2){
		ans = 1;
		for(i=1;i<=c;i++) ans = ans * i % MOD;
		for(i=1;i<=2*c-1;i+=2) ans = ans * i % MOD;
		for(i=a+c-1;i<=a+c-1+b-1;i++) ans = ans * i % MOD;
	}
	
	cout << ans << endl;
	
	return 0;
}
