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
const int N = 1e6 + 100;

int main() {
	int k; cin >> k;
	int n = 1;
	vector<vector<pair<int, int>>> g(k);
	vector<int> a(k), b(k), c(k);
	for (int i = 1; i < k; i++) {
		a[i] = n++;
		b[i] = n++;
		c[i] = n++;
	}
	for (int i = 1; i < k; i++) {
		g[0].pb(mp(0, a[i]));
		g[0].pb(mp(0, b[i]));
		g[0].pb(mp(b[i], c[i]));
	}
	for (int i = 1; i < k; i++) {
		g[i].pb(mp(c[i], 0));
	}
	for (int i = 1; i < k; i++) {
		for (int j = 1; j < k; j++) {
			g[i].pb(mp(a[i], b[j]));
			g[i].pb(mp(a[i], c[j]));
		}
	}
	for (int i = 1; i < k; i++) {
		for (int j = i + 1; j < k; j++) {
			g[i].pb(mp(a[i], a[j]));
			int x = n++;
			g[0].pb(mp(0, x));
			g[i].pb(mp(c[i], x));
			g[j].pb(mp(a[j], x));
			g[j].pb(mp(x, a[i]));
			for (int z = 1; z < k; z++) {
				if (z != i && z != j) {
					g[z].pb(mp(x, a[z]));
				}
			}
		}
	}
	cout << n << endl;
	for (const auto &tree : g) {
		for (const auto &edge : tree) {
			printf("%d %d\n", edge.fs + 1, edge.sc + 1);
		}
		puts("");
	}
    return 0;
}
