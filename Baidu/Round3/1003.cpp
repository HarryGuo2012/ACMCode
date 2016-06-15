#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#define MAX_N 10004

int n;

int H = 1040001;

std::vector<int> vm0, vm1, vy0, vy1;

std::vector<int> cnt0[MAX_N * 2], cnt1[MAX_N * 2];

std::vector<int> allA;

int ans = 0;
std::map<int, int> ma;
int maxVal[MAX_N * 2];

int tot = 0;

inline void init() {
	ans = 0;
	memset(maxVal, 0, sizeof(maxVal));
	vm0.clear();
	ma.clear();
	tot = 0;
	vm1.clear();
	allA.clear();
	vy0.clear();
	vy1.clear();
	for (int i = 0; i < MAX_N * 2; i++)
		cnt0[i].clear(), cnt1[i].clear();
}

void solve(std::vector<int> &vm, std::vector<int> &vy, std::vector<int> *cnt) {
	int res = 0;
	for (int i = 0; i < allA.size(); i++) {
		int A = allA[i];int mA = ma[A];
		int sum = std::lower_bound(vy.begin(), vy.end(), A + 1) - vy.begin();
		sum -= std::lower_bound(vm.begin(), vm.end(), A + 1) - vm.begin();
		sum += std::lower_bound(cnt[mA].begin(), cnt[mA].end(), A + 1) - cnt[mA].begin();
		maxVal[i] = std::max(maxVal[i], sum);
	}
}

void solve2(std::vector<int> &vm, std::vector<int> &vy, std::vector<int> *cnt) {
	int res = 0;
	int now = 0;
	for (int i = 0; i < allA.size(); i++) {
		int B = allA[i];
		now = std::max(now, maxVal[i]);
		int sum = std::lower_bound(vy.begin(), vy.end(), B + 1) - vy.begin();
		sum -= std::lower_bound(vm.begin(), vm.end(), B + 1) - vm.begin();
		sum += std::lower_bound(cnt[ma[B]].begin(), cnt[ma[B]].end(), B + 1) - cnt[ma[B]].begin();
		//if (B == 3) printf("%d\n", sum);
		ans = std::max(ans, now + sum);
	}
}

int T;

int main() {
	scanf("%d", &T);
	for (int c = 1; c <= T; c++) {
	init();
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		int x, y, z, d;
		scanf("%d%d%d%d", &x, &y, &z, &d);
		if (d == 1) {
			allA.push_back(x + z);
			allA.push_back(y - z);
			vm0.push_back(std::max(x + z, y - z));
			vy0.push_back(y - z);
			if (ma.find(x + z) == ma.end()) ma[x + z] = ++tot;
			cnt0[ma[x + z]].push_back(y - z);
		}
		else { 
			allA.push_back(x + z);
			allA.push_back(y - z);
			vm1.push_back(std::max(x + z, y - z));
			vy1.push_back(y - z);
			if (ma.find(x + z) == ma.end()) ma[x + z] = ++tot;
			cnt1[ma[x + z]].push_back(y - z);
		}
	}
	std::sort(allA.begin(), allA.end());
	for (int i = 0; i < 2 * MAX_N; i++)
		std::sort(cnt0[i].begin(), cnt0[i].end());
	for (int i = 0; i < 2 * MAX_N; i++)
		std::sort(cnt1[i].begin(), cnt1[i].end());
	std::sort(vm0.begin(), vm0.end());
	std::sort(vm1.begin(), vm1.end());
	std::sort(vy0.begin(), vy0.end());
	std::sort(vy1.begin(), vy1.end());
	solve(vm0, vy0, cnt0);
	solve2(vm1, vy1, cnt1);
	printf("Case #%d:\n%d\n", c, ans);
}
	return 0;
}