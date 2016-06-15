#include <cstdio>
#include <queue>
#include <functional>
#include <algorithm>

#define MAX_N 100005

typedef std::pair<int, int> P;

std::priority_queue<int> que;
P rabbit[MAX_N];
int N;

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d", &rabbit[i].first);
	for (int i = 0; i < N; i++)
		scanf("%d", &rabbit[i].second);
	std::sort(rabbit, rabbit + N);
	int j = N - 1, ans = 0;
	for (int time = 5000; time >= 1; time--) {
		while(j >= 0 && rabbit[j].first == time) {
			que.push(rabbit[j].second);
			j--;
		}
		if(que.size()) {
			ans += que.top();
			que.pop();
		}
	}
	printf("%d\n", ans);
	return 0;
}