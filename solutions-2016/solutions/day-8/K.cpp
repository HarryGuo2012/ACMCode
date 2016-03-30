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
struct point {ll x,y;};

ll prod(point P, point Q){
	return P.x * Q.x + P.y * Q.y;
}

point func(point Q, point P){
	ll y = prod(P, Q);
	ll x = prod(P, P);
	if(x < 0){
		x = -x;
		y = -y;
	}
	bool neg = (y < 0);
	if(y < 0) y = -y;
	ll z = (2 * y + x) / (2 * x);
	if(neg) z = -z;
	Q.x -= P.x * z;
	Q.y -= P.y * z;
	return Q;
}

point gcd(point P, point Q){
	if(prod(P, P) > prod(Q, Q)) swap(P, Q);
	if(prod(P, P) == 0) return Q;
	Q = func(Q, P);
	swap(P.x, P.y);
	P.x = -P.x;
	Q = func(Q, P);
	return gcd(Q, P);
}

int x[100010],y[100010];
ll s[100010],t[100010];

int main(void){
	int N,i;
	
	cin >> N;
	REP(i,N) scanf("%d%d", &x[i], &y[i]);
	
	if(N == 1){
		cout << 0 << endl;
		return 0;
	}
	
	point P = {x[1] - x[0], y[1] - y[0]};
	for(i=2;i<N;i++){
		point Q = {x[i] - x[0], y[i] - y[0]};
		P = gcd(P, Q);
	}
	
	ll a = P.x, b = P.y;
	REP(i,N){
		s[i] = x[i] * a + y[i] * b;
		t[i] = y[i] * a - x[i] * b;
	}
	sort(s, s+N);
	sort(t, t+N);
	
	ll ans = max(s[N-1] - s[0], t[N-1] - t[0]) / (a*a + b*b);
	ans = (ans + 1) * (ans + 1) - N;
	cout << ans << endl;
	
	return 0;
}
