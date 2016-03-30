#include<cmath>
#include<cassert>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int cnt;

int g(int n, int m) {
	--cnt;
	int ret = 0;
	for (int i = 1; i <= n; ++i) {
		ret += m % i;
	}
	return ret;
}

const int N = 10005;

int n;

int to[N * (N - 1) / 2 + 1];

int myRand() {
	return (rand() << 15) ^ rand();
}

int ans;

inline void go(int i) {
	if (to[i] == -1) {
		int cur = i, tot = 0;
		while (to[cur] == -1) {
			++tot;
			to[cur] = g(n, cur);
			cur = to[cur];
		}
		int plen = 0, base = cur;
		cur = i;
		while (cur != base) {
			++plen;
			cur = to[cur];
		}
		ans = max(ans, tot - plen);
	}
}

int main() {
	scanf("%d", &n);
	memset(to, -1, sizeof(to));
	ans = 1;
	if (n < 500) {
		int bar = n * (n - 1) / 2 + 1;
		for (int i = 1; i < bar; ++i) {
			go(i);
		}
	} else {
		cnt = 400000000 / n;
		int ub = n * (n - 1) / 2 * 3 / 5,
			lb = ub / 2,
			mod = ub - lb;
		while (cnt > 0) {
			int i = 1;
			i = myRand() % mod;
			if (i < 0) {
				i += mod;
			}
			i += lb;	
			if (to[i] != -1) {
				cnt -= 100;
			} else {
				go(i);
			}
		}
	}
	cout << ans << endl;
	return 0;
}