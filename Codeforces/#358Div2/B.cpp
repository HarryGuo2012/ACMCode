#include <cstdio>
#include <queue>
#include <algorithm>
#include <functional>

std::priority_queue<int, std::vector<int>, std::greater<int> > que;

int main() {
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		int a;
		scanf("%d", &a);
		que.push(a);
	}
	int now = 0;
	while (que.size()) {
		int u = que.top();
		que.pop();
		if (u >= now + 1) now++;
	}
	printf("%d\n", now + 1);
	return 0;
}