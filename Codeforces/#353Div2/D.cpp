#include <cstdio>
#include <algorithm>
#include <map>
#include <set>
#include <vector>

#define MAX_N 100005

int n;
int a[MAX_N];
std::map<int, int> ma;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) 
		scanf("%d", &a[i]);

	ma[0] = a[1];
	for (int i = 2; i <= n; i++) {
		auto it = ma.lower_bound(a[i]);
		it--;
		int t = it->first, u = it->second;
		printf("%d%c", u, i == n ? '\n' : ' ');
		if (a[i] > u) ma[u] = a[i];
		else {
			if (ma[u] == 0) ma[u] = u;
			ma[t] = a[i];
		}
	}
	return 0;
}