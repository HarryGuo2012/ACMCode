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

int a[1010];

int main(void){
	int N,i;
	
	cin >> N;
	REP(i,N) cin >> a[i];
	
	sort(a, a+N);
	
	int ans = 0, sum = 0;
	REP(i,N) if(a[i] > sum){
		sum += a[i];
		ans++;
	}
	
	cout << ans << endl;
	
	return 0;
}
