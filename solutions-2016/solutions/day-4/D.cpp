#include <algorithm>
#include <cassert>
#include <climits>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <functional>
#include <utility>
#include <vector>

const int N = 200000;
const int D = 20;

int weight[N], a[N], b[N];
std::vector<int> tree[N];

int depth[N], jump[N][D], order[N], position[N], end_position[N], sum[N + 1];
std::vector<int> children[N];

void prepare(int u, int p, int &&count) {
    depth[u] = ~p ? depth[p] + 1 : 0;
    memset(jump[u], -1, sizeof(jump[u]));
    jump[u][0] = p;
    for (int i = 0; ~jump[u][i]; ++ i) {
        jump[u][i + 1] = jump[jump[u][i]][i];
    }
    order[position[u] = count ++] = u;
    for (int v : tree[u]) {
        if (v != p) {
            prepare(v, u, std::move(count));
        }
    }
    end_position[u] = count;
}

int lca(int a, int b) {
    if (depth[a] > depth[b]) {
        std::swap(a, b);
    }
    for (int i = D - 1; i >= 0; -- i) {
        if (depth[b] - depth[a] >> i & 1) {
            b = jump[b][i];
        }
    }
    for (int i = D - 1; i >= 0; -- i) {
        if (jump[a][i] != jump[b][i]) {
            a = jump[a][i];
            b = jump[b][i];
        }
    }
    return a == b ? a : jump[a][0];
}

bool by_position(int i, int j) {
    return position[b[i]] < position[b[j]];
}

bool is_descendant(int a, int b) {
    return position[a] <= position[b] && position[b] < end_position[a];
}

int subtree_size(int v) {
    return sum[position[v]] - sum[end_position[v]];
}

bool by_subtree_size(int u, int v) {
    return subtree_size(u) > subtree_size(v);
}

int random_() {
#ifdef __linux__
    return rand();
#else
    return rand() << 15 ^ rand();
#endif
}

int solve(const std::vector<int> &cuts, int root) {
    std::vector<int> subtrees;
    for (int c : cuts) {
        int v = b[c];
        if (root != v && is_descendant(root, v)) {
            if (!subtrees.empty() && is_descendant(subtrees.back(), v)) {
                continue;
            }
            subtrees.push_back(v);
        }
    }
    std::vector<std::pair<int, int>> parts;
    if (subtrees.empty()) {
        parts.push_back({position[root], end_position[root]});
    } else {
        parts.push_back({position[root], position[subtrees[0]]});
        for (int i = 1; i < (int)subtrees.size(); ++ i) {
            parts.push_back({end_position[subtrees[i - 1]], position[subtrees[i]]});
        }
        parts.push_back({end_position[subtrees.back()], end_position[root]});
    }
    std::function<int (int)> now_subtree_size = [&](int v) -> int {
        int s = subtree_size(v);
        for (int u : subtrees) {
            if (is_descendant(v, u)) {
                s -= subtree_size(u);
            }
        }
        return s;
    };
    int total = now_subtree_size(root);
    std::function<int ()> choice = [&]() -> int {
        int id = random_() % total;
        for (const auto &part : parts) {
            int length = sum[part.first] - sum[part.second];
            if (id < length) {
                int index = (int)(std::upper_bound(sum + part.first, sum + part.second, sum[part.first] - id, std::greater<int>()) - sum) - 1;
                return order[index];
            } else {
                id -= length;
            }
        }
        assert(false);
    };
    std::function<int (int, int)> check = [&](int a, int b) -> int {
        for (int i = D - 1; i >= 0; -- i) {
            if (depth[a] - (1 << i) >= depth[b]) {
                int v = jump[a][i];
                if (now_subtree_size(v) * 2 <= total) {
                    a = v;
                }
            }
        }
        if (a != b) {
            a = jump[a][0];
        }
        std::pair<int, int> m(total - now_subtree_size(a), jump[a][0]);
        for (int i = 0; i < (int)children[a].size() && i <= (int)subtrees.size(); ++ i) {
            int v = children[a][i];
            m = std::max(m, {now_subtree_size(v), v});
        }
        int result = INT_MAX;
        if (m.first + m.first <= total) {
            result = a;
        }
        if (m.first + m.first == total) {
            result = std::min(result, m.second);
        }
        return result;
    };
    while (true) {
        int a = choice();
        int b = choice();
        int c = lca(a, b);
        int result = check(a, c);
        if (result != INT_MAX) {
            return result;
        }
        result = check(b, c);
        if (result != INT_MAX) {
            return result;
        }
    }
}

int main() {
    int n, q;
    scanf("%d%d", &n, &q);
    for (int i = 0; i < n; ++ i) {
        scanf("%d", weight + i);
    }
    for (int i = 0; i < n - 1; ++ i) {
        scanf("%d%d", a + i, b + i);
        a[i] --;
        b[i] --;
        tree[a[i]].push_back(b[i]);
        tree[b[i]].push_back(a[i]);
    }
    prepare(0, -1, 0);
    for (int i = 0; i < n; ++ i) {
        if (depth[a[i]] > depth[b[i]]) {
            std::swap(a[i], b[i]);
        }
    }
    sum[n] = 0;
    for (int i = n - 1; i >= 0; -- i) {
        sum[i] = sum[i + 1] + weight[order[i]];
    }
    for (int i = 0; i < n; ++ i) {
        for (int v : tree[i]) {
            if (v != jump[i][0]) {
                children[i].push_back(v);
            }
        }
        std::sort(children[i].begin(), children[i].end(), by_subtree_size);
    }
    while (q --) {
        int m;
        scanf("%d", &m);
        std::vector<int> cuts;
        for (int i = 0; i < m; ++ i) {
            int cut;
            scanf("%d", &cut);
            cuts.push_back(-- cut);
        }
        std::sort(cuts.begin(), cuts.end(), by_position);
        std::vector<int> result;
        result.push_back(solve(cuts, 0));
        for (int i = 0; i < m; ++ i) {
            result.push_back(solve(cuts, b[cuts[i]]));
        }
        std::sort(result.begin(), result.end());
        for (int i = 0; i <= m; ++ i) {
            printf("%d%c", result[i] + 1, " \n"[i == m]);
        }
    }
    return 0;
}
