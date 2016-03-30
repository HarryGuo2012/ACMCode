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

int N;
int a[30];
int c[30];
vector <int> v;

void generate(int x){
	int d = 1;
	while((d+1)*(d+1) <= x) d++;
	for(int i=1;i<=d+2;i++) v.push_back(i);
	for(int i=1;i<=d+2;i++) v.push_back((x+i-1)/i);
}

bool check(int x){
	int i;
	REP(i,N-1) if(((a[i] - 1) / x == (a[i+1] - 1) / x) != (c[i] == c[i+1])) return false;
	return true;
}

int main(void){
	int i,j,k;
	
	cin >> N;
	REP(i,N) cin >> a[i] >> c[i];
	
	REP(k,N) REP(j,k) REP(i,j) if(c[i] == c[k] && c[i] != c[j]){
		cout << 0 << endl;
		return 0;
	}
	
	REP(i,N) generate(a[i]);
	sort(v.begin(),v.end());
	int sz = v.size();
	
	int ans = 0;
	
	REP(i,sz){
		if(check(v[i])){
			if(i == sz-1){
				cout << -1 << endl;
				return 0;
			}
			ans += v[i+1] - v[i];
		}
	}
	
	cout << ans << endl;
	
	return 0;
}
