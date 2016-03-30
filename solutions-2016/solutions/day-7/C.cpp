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
const ld pi = 4 * atanl(1);
const int full = 3600 * 360;

void answer(ld angle) {
	puts("YES");
	printf("%d %d\n", (int) (1e9 * cos(angle)), (int) (1e9 * sin(angle)));
	exit(0);
}

int n;

int main() {
	cin.tie(0);
	cin >> n;
	vector<pair<int, int>> events;
	for (int i = 0; i < n; i++) {
		int x, y, phi, alpha; scanf("%d%d%d%d", &x, &y, &alpha, &phi);
		events.pb(mp(phi, -1));
		if (phi + alpha > full) {
			events.pb(mp(full - 1, 1));
			events.pb(mp(0, -1));
			events.pb(mp(phi + alpha - full - 1, 1));
		} else {
			events.pb(mp(phi + alpha - 1, 1));
		}
	}
	for (int i = 0; i < full; i++) {
		events.pb(mp(i, 0));
	}
	sort(all(events));
	int cur = 0;
	for (const auto &event : events) {
		if (event.sc == -1) {
			cur += 1;
		} else if (cur == 0) {
			answer((event.fs + 0.5) / full * 2 * pi);
		} else if (event.sc == 1) {
			cur -= 1;
		}
	} 
	puts("NO");
    return 0;
}
