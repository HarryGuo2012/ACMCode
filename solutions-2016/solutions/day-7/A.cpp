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
const int N = 1e3 + 100;
const int ITERS = 3;

inline int64 myrand() {
	return abs((((int64) rand()) << 16) + rand());
}

inline bool isPrime(int n) {
	if (n == 1) {
		return false;
	}
	for (int i = 2; i * i <= n; i++) {
		if (n % i == 0) {
			return false;
		}
	}
	return true;
}

inline int randomPrime(int l, int r) {
	int n = myrand() % (r - l + 1) + l;
	while (!isPrime(n)) {
		n++;
	}
	return n;
}

inline int power(int a, int b, int M) {
	int res = 1;
	while (b) {
		if (b & 1) {
			res = (1ll * res * a) % M;
		}
		a = (1ll * a * a) % M;
		b >>= 1;
	}
	return res;
}

inline int inv(int a, int M) {
	return power(a, M - 2, M);
}

int n, m;
int a[N][N];

int t[N][N];

inline int solve(int M) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			t[i][j] = a[i][j];
		}
	}
	for (int i = 0; i < n; i++) {
	    for (int j = 0; j < m; j++) {
	        a[i][j] = (a[i][j] % M + M) % M;
	    }
	}
	int it = 0, ans = 0;
	for (int i = 0; i < n && it < m; i++) {
		int index = -1;
		for (int j = i; j < n; j++) {
			if (a[j][it]) {
				index = j;
				break;
			}
		}
		if (index == -1) {
			i--, it++;
			continue;
		}
		ans++;
		for (int j = 0; j < m; j++) {
			swap(a[index][j], a[i][j]);
		}
		for (int j = i + 1; j < n; j++) {
			if (a[j][it] == 0) {
				continue;
			}
			int q = (1ll * inv(a[i][it], M) * a[j][it]) % M;
			for (int z = it; z < m; z++) {
				a[j][z] = (a[j][z] - ((1ll * q * a[i][z]) % M));
				if (a[j][z] < 0) {
					a[j][z] += M;
				}
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			a[i][j] = t[i][j];
		}
	}
	return ans;
}

int main() {
	srand(-1);
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", &a[i][j]);
		}
	}
	int ans = 0;
	for (int t = 0; t < ITERS; t++) {
		ans = max(ans, solve(randomPrime(9e8, 1e9)));
	}
	cout << ans << endl;
    return 0;
}
