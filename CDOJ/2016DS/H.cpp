#include <cstdio>
#include <vector>
#include <algorithm>

#define MAX_N 1000006

typedef std::pair<int, int> P;

int father[MAX_N];

void init () {
	for (int i = 0; i < MAX_N; i++) 
		father[i] = i;
}

int Find (int x) {
	if (x == father[x]) return x;
	return father[x] = Find(father[x]);
}

void unionSet (int x, int y) {
	int u = Find(x), v = Find(y);
	if (u == v) return;
	father[u] = v;
}

int n, m;

std::vector<P> row[MAX_N], colum[MAX_N];
std::vector<P> allNode;

int Hash(int i, int j) {
	return i * m + j;
}

int code[MAX_N];

int main() {
	std::fill(code, code + MAX_N, 1);
	init();
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			int a;
			scanf("%d", &a);
			row[i].push_back(std::make_pair(a, j));
			colum[j].push_back(std::make_pair(a, i));
			allNode.push_back(std::make_pair(a, i * m + j));
		}
	for (int i = 0; i < n; i++)
		std::sort(row[i].begin(), row[i].end());
	for (int j = 0; j < m; j++)
		std::sort(colum[j].begin(), colum[j].end());

	for (int i = 0; i < n; i++)
		for (int j = 0; j < row[i].size(); j++) 
			if (j != 0 && row[i][j].first == row[i][j - 1].first) {
				int u = Hash(i, row[i][j - 1].second), v = Hash(i, row[i][j].second);
				unionSet(u, v);
			}

	for (int j = 0; j < m; j++)
		for (int i = 0; i < colum[j].size(); i++)
			if(i != 0 && colum[j][i].first == colum[j][i - 1].first) {
				int u = Hash(colum[j][i - 1].second, j), v = Hash(colum[j][i].second, j);
				unionSet(u, v);
			}

	std::sort(allNode.begin(), allNode.end());

	for (auto u : allNode) {
		int i = u.second / m, j = u.second % m;
		int a = u.first;
		if (a < row[i][row[i].size() - 1].first) {
			int r = row[i].size() - 1, l = 0;
			while (r - l > 1) {
				int mid = (r + l) >> 1;
				if (row[i][mid].first > a) r = mid;
				else l = mid;
			}
			int p = Hash(i, row[i][r].second);
			code[Find(p)] = std::max(code[Find(p)], code[Find(u.second)] + 1);
		}

		if (a < colum[j][colum[j].size() - 1].first) {
			int r = colum[j].size() - 1, l = 0;
			while (r - l > 1) {
				int mid = (r + l) >> 1;
				if (colum[j][mid].first > a) r = mid;
				else l = mid;
			}
			int p = Hash(colum[j][r].second, j);
			code[Find(p)] = std::max(code[Find(p)], code[Find(u.second)] + 1);
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int u = Hash(i, j);
			printf("%d ", code[Find(u)]);
		}
		printf("\n");
	}
	return 0;
}