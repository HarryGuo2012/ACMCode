#include <iostream>
#include <algorithm>

using namespace std;

const int MOD = (int)1e9 + 7;
const int N = 2000 + 10;

struct Info
{
	int value, ways;
	Info(int value = 0, int ways = 0) : value(value), ways(ways) {}
	Info operator + (const Info &that) const {
		Info ret = *this;
		if (that.value > ret.value) {
			ret = that;
		} else if (that.value == ret.value) {
			ret.ways += that.ways;
			if (ret.ways >= MOD) ret.ways -= MOD;
		}
		return ret;
	}
	Info operator + (const int &that) const {
		Info ret = *this;
		ret.value += that;
		return ret;
	}
};

int n, s;
int w[N];
Info f[N][N];

void solve(int l, int r, int dep)
{
	if (l == r) {
		for(int i = 0; i <= r - l + 1; ++ i) {
			f[dep][i] = Info(0, 1);
		}
		return;
	}
	if (w[l] + w[r] < s) {
		solve(l + 1, r, dep + 1);
		for(int i = 0; i <= r - l; ++ i) {
			f[dep][i] = f[dep][i] + f[dep + 1][i];
			f[dep][i + 1] = f[dep][i + 1] + f[dep + 1][i];
		}
	} else {
		solve(l, r - 1, dep + 1);
		for(int i = 0; i <= r - l; ++ i) {
			f[dep][i] = f[dep][i] + (f[dep + 1][i] + i);
			f[dep][i + 1] = f[dep][i + 1] + (f[dep + 1][i] + (r - l - i));
		}
	}
}

void solve()
{
	cin >> n >> s;
	for(int i = 0; i < n; ++ i) {
		cin >> w[i];
	}
	sort(w, w + n);
	solve(0, n - 1, 0);
	Info ret(0, 0);
	for(int i = 0; i <= n; ++ i) {
		ret = ret + f[0][i];
	}
	cout << ret.value << ' ' << ret.ways << endl;
}

int main()
{
	solve();
	return 0;
}
