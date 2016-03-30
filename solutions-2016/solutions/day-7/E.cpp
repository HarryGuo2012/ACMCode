#include <iostream>
#include <fstream>
#include <sstream>

#include <vector>
#include <set>
#include <bitset>
#include <map>
#include <deque>
#include <string>

#include <algorithm>
#include <numeric>

#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cmath>

#define pb push_back
#define pbk pop_back
#define mp make_pair
#define fs first
#define sc second
#define all(x) (x).begin(), (x).end()
#define foreach(i, a) for (__typeof((a).begin()) i = (a).begin(); i != (a).end(); ++i)
#define len(a) ((int) (a).size())

#ifdef CUTEBMAING
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define eprintf(...) 42
#endif

using namespace std;

typedef long long int64;
typedef long double ld;
typedef unsigned long long lint;

const int inf = (1 << 30) - 1;
const int64 linf = (1ll << 62) - 1;

vector<int> ans;
set<int> st;

void solve(int i) {
	if (st.find(i) == st.end()) {
		ans.pb(i);
		return ;
	}
	solve(i * 2);
	solve(i * 2 + 1);
}

bool check(int a, int b) {
	while (a > 0) {
		if (a == b) {
			return true;
		}
		a >>= 1;
	}
	return false;
}

int main() {
	int a, b; cin >> a >> b;
	if (check(a, b) || check(b, a)) {
		puts("-1");
		return 0;
	}
	while (a > 1) {
		a >>= 1;
		st.insert(a);
	}
	while (b > 1) {
		b >>= 1;
		st.insert(b);
	}
	solve(1);
	sort(all(ans));
	ans.resize(unique(all(ans)) - ans.begin());
	for (int i : ans) {
		printf("%d ", i);
	}
	puts("");
    return 0;
}
