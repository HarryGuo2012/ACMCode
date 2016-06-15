#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

#define MAX_N 1000006

std::queue<int> que;

int tree[MAX_N], n;

void add(int a, int x) {
	while (a < MAX_N) {
		tree[a] += x;
		a += a & (-a);
	}
}

int findKth(int k) {
    int ans = 0, cnt = 0, i;
    for (i = 20; i >= 0; i--) {
        ans += (1 << i);
        if (ans >= MAX_N || cnt + tree[ans] >= k)
            ans -= (1 << i);
        else
            cnt += tree[ans];
    }
    return ans + 1;
}

typedef std::pair<int, int> P;

std::vector<P> vp;

std::vector<int> allX;

int main() {
	scanf("%d", &n);
	while (n--) {
		int op, x = 0;
		scanf("%d", &op);
		if (op == 1) {
			scanf("%d", &x);
			allX.push_back(x);
		}
		vp.push_back(std::make_pair(op, x));
	}

	std::sort(allX.begin(), allX.end());
	auto it = std::unique(allX.begin(), allX.end());
	allX.resize(std::distance(allX.begin(), it));

	for (auto p : vp) {
		int op = p.first, x = std::lower_bound(allX.begin(), allX.end(), p.second) - allX.begin() + 1;
		if (op == 1) {
			que.push(x);
			add(x, 1);
		}
		else if(op == 2) {
			add(que.front(), -1);
			que.pop();
		}
		else 
			printf("%d\n", allX[findKth(que.size() / 2 + 1) - 1]);
	}
	return 0;
}