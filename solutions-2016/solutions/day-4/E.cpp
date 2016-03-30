#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

#define ALL(v) (v).begin(), (v).end()

const int N = 2000;
const int MOD = (int)1e9 + 7;

std::vector<int> edges[N];
bool graph[N][N], used[N];
int n, parent[N], height[N], related[N];
std::vector<int> group_by_height[N], children_hash[N], order;
int hash_size, hash[N], tree_automorphism[N], permutation[N], result;

bool by_children_hash_and_parent(int i, int j) {
    if (children_hash[i] != children_hash[j]) {
        return children_hash[i] < children_hash[j];
    }
    return parent[i] < parent[j];
}

void dfs(int u) {
    order.push_back(u);
    for (int v : edges[u]) {
        if (related[v] == -1) {
            related[v] = u;
            dfs(v);
        }
    }
}

void search(int i) {
    if (i == (int)order.size()) {
        int aut = 1;
        for (int v : order) {
            int u = permutation[v];
            if (hash[u] != hash[v]) {
                aut = 0;
            } else {
                aut = (long long)aut * tree_automorphism[u] % MOD;
            }
        }
        result += aut;
        if (result >= MOD) {
            result -= MOD;
        }
    } else {
        int v = order[i];
        std::vector<int> candidates;
        if (!i) {
            for (int j = 0; j < n; ++ j) {
                if (edges[v].size() == edges[j].size()) {
                    candidates.push_back(j);
                }
            }
        } else {
            for (int u : edges[permutation[related[v]]]) {
                if (!used[u]) {
                    candidates.push_back(u);
                }
            }
        }
        for (int p : candidates) {
            permutation[v] = p;
            bool checked = true;
            for (int u : edges[v]) {
                if (permutation[u] != -1) {
                    checked &= graph[permutation[u]][permutation[v]];
                }
            }
            if (checked) {
                used[p] = true;
                search(i + 1);
                used[p] = false;
            }
        }
        permutation[v] = -1;
    }
}

int main() {
    int m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++ i) {
        int a, b;
        scanf("%d%d", &a, &b);
        a --;
        b --;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }
    std::vector<int> queue;
    for (int i = 0; i < n; ++ i) {
        if ((int)edges[i].size() == 1) {
            queue.push_back(i);
        }
    }
    memset(parent, -1, sizeof(parent));
    for (int head = 0; head < (int)queue.size(); ++ head) {
        int v = queue[head];
        if (edges[v].empty()) {
            break;
        }
        int p = parent[v] = edges[v][0];
        height[p] = std::max(height[p], height[v] + 1);
        edges[p].erase(std::find(ALL(edges[p]), v));
        if ((int)edges[p].size() == 1) {
            queue.push_back(p);
        }
    }
    for (int i = 0; i < n; ++ i) {
        tree_automorphism[i] = 1;
        group_by_height[height[i]].push_back(i);
    }
    hash_size = 1;
    for (int h = 0; h < n; ++ h) {
        std::sort(ALL(group_by_height[h]), by_children_hash_and_parent);
        for (int i = 0; i < (int)group_by_height[h].size();) {
            int j = i;
            int last_parent = -1;
            int last_children_count = 0;
            while (j < (int)group_by_height[h].size()) {
                int v = group_by_height[h][j];
                if (children_hash[group_by_height[h][i]] != children_hash[v]) {
                    break;
                }
                hash[v] = hash_size;
                int p = parent[v];
                if (p != -1) {
                    children_hash[p].push_back(hash[v]);
                    tree_automorphism[p] = (long long)tree_automorphism[p] * tree_automorphism[v] % MOD;
                    if (last_parent != p) {
                        last_parent = p;
                        last_children_count = 0;
                    }
                    last_children_count ++;
                    tree_automorphism[p] = (long long)tree_automorphism[p] * last_children_count % MOD;
                }
                j ++;
            }
            i = j;
            hash_size ++;
        }
    }
    int root = 0;
    while (root < n && (int)edges[root].size() != 2) {
        root ++;
    }
    for (int i = 0; i < n; ++ i) {
        if (edges[i].size() > edges[root].size()) {
            root = i;
        }
    }
    memset(related, -1, sizeof(related));
    related[root] = root;
    dfs(root);
    for (int i = 0; i < n; ++ i) {
        for (int j : edges[i]) {
            graph[i][j] = true;
        }
    }
    memset(permutation, -1, sizeof(permutation));
    search(0);
    printf("%d\n", result);
    return 0;
}
