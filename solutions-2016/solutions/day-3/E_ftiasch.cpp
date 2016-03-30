#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>
#include <vector>
#include <queue>
#include <algorithm>

const int N = 100000 + 1;
const int D = 20;

int weight[N], depth[N], jump[N][D];
std::vector <int> tree[N];

void preprocess(int p, int u)
{
	depth[u] = ~p ? depth[p] + 1 : 0;
	jump[u][0] = p;
	for (int i = 0; ~jump[u][i]; ++ i) {
		jump[u][i + 1] = jump[jump[u][i]][i];
	}
	for (int i = 0; i < (int)tree[u].size(); ++ i) {
		int v = tree[u][i];
		if (v != p) {
			preprocess(u, v);
		}
	}
}

int get_lca(int u, int v)
{
	if (depth[u] > depth[v]) {
		std::swap(u, v);
	}
	for (int i = D - 1; i >= 0; -- i) {
		if (depth[v] - depth[u] >> i & 1) {
			v = jump[v][i];
		}
	}
	if (u == v) {
		return u;
	}
	for (int i = D - 1; i >= 0; -- i) {
		if (jump[u][i] != jump[v][i]) {
			u = jump[u][i];
			v = jump[v][i];
		}
	}
	return jump[u][0];
}

int id[N][D];

const int V = 2 + N + N * D;
const int E = (N * D * 4 + N) * 2;

int edge_count, head[V], to[E], capacity[E], old_capacity[E], next[E];

void _add_edge(int u, int v, int w)
{
	to[edge_count] = v;
	capacity[edge_count] = w;
	old_capacity[edge_count] = w;
	next[edge_count] = head[u];
	head[u] = edge_count ++;
}

void add_edge(int u, int v, int w)
{
	_add_edge(u, v, w);
	_add_edge(v, u, 0);
}

void cover(int v, int u, int d)
{
	for (int i = D - 1; i >= 0; -- i) {
		if (d >> i & 1) {
			add_edge(v, id[u][i], INT_MAX);
			u = jump[u][i];
		}
	}
}

int level[V], current[V];

int dfs(int u, int target, int left)
{
	if (u == target) {
		return left;
	}
	int delta = 0;
	for (int &it = current[u]; ~it; it = next[it]) {
		int v = to[it];
		if (capacity[it] > 0 && level[v] == level[u] + 1) {
			int tmp = dfs(v, target, std::min(left - delta, capacity[it]));
			capacity[it] -= tmp;
			capacity[it ^ 1] += tmp;
			delta += tmp;
			if (delta == left) {
				return delta;
			}
		}
	}
	level[u] = -1;
	return delta;
}

int solve(int source, int target, int n)
{
	int ret = 0;
	while (true) {
		memset(level, -1, sizeof(level));
		level[source] = 0;
		std::queue <int> queue;
		queue.push(source);
		while (!queue.empty() && level[target] == -1) {
			int u = queue.front();
			queue.pop();
			for (int it = head[u]; ~it; it = next[it]) {
				int v = to[it];
				if (capacity[it] > 0 && level[v] == -1) {
					level[v] = level[u] + 1;
					queue.push(v);
				}
			}
		}
		if (level[target] == -1) {
			return ret;
		}
		for (int i = 0; i < n; ++ i) {
			current[i] = head[i];
		}
		ret += dfs(source, target, INT_MAX);
	}
	return ret;
}

int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++ i) {
		weight[i] = 1;
	}
	tree[0].push_back(1);
	for (int i = 0; i < n - 1; ++ i) {
		int a, b;
		scanf("%d%d", &a, &b);
		tree[a].push_back(b);
		tree[b].push_back(a);
	}
	memset(jump, -1, sizeof(jump));
	preprocess(-1, 0);
	int count = 0;
	int target = count ++;
	memset(id, -1, sizeof(id));
	memset(head, -1, sizeof(head));
	edge_count = 0;
	for (int i = 1; i <= n; ++ i) {
		id[i][0] = count ++;
		add_edge(id[i][0], target, weight[i]);
	}
	for (int j = 1; j < D; ++ j) {
		for (int i = 1; i <= n; ++ i) {
			if (~jump[i][j]) {
				id[i][j] = count ++;
				add_edge(id[i][j], id[i][j - 1], INT_MAX);
				add_edge(id[i][j], id[jump[i][j - 1]][j - 1], INT_MAX);
			}
		}
	}
	int source = count ++;
	int start = count;
	for (int _ = 0; _ < n; ++ _) {
		int a, b;
		int c = 1;
		scanf("%d%d", &a, &b);
		int v = count ++;
		add_edge(source, v, c);
		c = get_lca(a, b);
		cover(v, a, depth[a] - depth[c] + 1);
		cover(v, b, depth[b] - depth[c] + 1);
	}
	assert(count <= V);
	assert(edge_count <= E);
	int result = solve(source, target, count);
	if (result < n) {
		puts("No");
	} else {
		puts("Yes");
		memcpy(current, head, sizeof(*head) * count);
		std::vector<int> plan(n);
		while (result --) {
			std::vector<int> edges;
			int v = target;
			while (v != source) {
				int &e = current[v];
				while (e != -1 && (old_capacity[e] != 0 || capacity[e] == 0)) {
					e = next[e];
				}
				assert(e != -1);
				edges.push_back(e);
				v = to[e];
				capacity[e] --;
			}
			int f = to[edges.front()];
			int t = to[edges.back() ^ 1];
			assert(1 <= f && f <= n);
			assert(start <= t && t < start + n);
			plan[t - start] = f;
		}
		for (int i = 0; i < n; ++ i) {
			printf("%d%c", plan[i], " \n"[i == n - 1]);
		}
	}
	return 0;
}
