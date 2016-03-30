#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <climits>
#include <utility>
#include <vector>

typedef long long Long;

const int N = 200000;
const int M = 16;
const int T = M + M - 1;
const Long INF = 1LL << 62;

int get_id(int l, int r) {
    return l + r | l != r;
}

std::vector<int> includeOne[M], excludeOne[M], include[M * M * M], exclude[M * M * M];

void product(std::vector<int> one[], std::vector<int> all[]) {
    for (int a = 0; a < M; ++ a) {
        for (int b = 0; b < M; ++ b) {
            for (int c = 0; c < M; ++ c) {
                int m = (a * M + b) * M + c;
                for (int ai : one[a]) {
                    for (int bi : one[b]) {
                        for (int ci : one[c]) {
                            all[m].push_back((ai * T + bi) * T + ci);
                        }
                    }
                }
                std::sort(all[m].begin(), all[m].end());
            }
        }
    }
}

Long id[N];

Long get_id(int i) {
    if (i < 0) {
        return -1;
    }
    if (i >= N) {
        return INF + 1;
    }
    return id[i];
}

bool cmp(int i, int j) {
    return get_id(i) < get_id(j);
}

struct DS {
    void clear() {
        min = min2 = N;
        max = max2 = -1;
        mind = maxd = -1;
    }

    void insert(int d, int v) {
        if (cmp(v, min)) {
            if (d != mind) {
                min2 = min;
                mind = d;
            }
            min = v;
        } else if (d != mind && cmp(v, min2)) {
            min2 = v;
        }
        if (cmp(max, v)) {
            if (d != maxd) {
                max2 = max;
                maxd = d;
            }
            max = v;
        } else if (d != maxd && cmp(max2, v)) {
            max2 = v;
        }
    }

    int get_min(int d) {
        return mind == d ? min2 : min;
    }

    int get_max(int d) {
        return maxd == d ? max2 : max;
    }

    int min, min2, mind, max, max2, maxd;
};

DS ds[T * T * T];

int children[N + 1][2], weight[N + 1], size[N + 1];

void update(int x) {
    size[x] = size[children[x][0]] + 1 + size[children[x][1]];
}

void rotate(int &x, int t) {
    int y = children[x][t];
    children[x][t] = children[y][1 ^ t];
    children[y][1 ^ t] = x;
    update(x);
    update(y);
    x = y;
}

void rebuild(int &x, Long l, Long r) {
    if (x != N) {
        id[x] = l + r >> 1;
        rebuild(children[x][0], l, id[x]);
        rebuild(children[x][1], id[x], r);
    }
}

bool insert(int &x, int u, int s, Long l, Long r) {
    if (x == N) {
        x = u;
        assert(l + 1 != r);
        id[u] = l + r >> 1;
        size[x] = 1;
        weight[x] = rand();
        children[x][0] = children[x][1] = N;
        return true;
    } else {
        if (s <= size[children[x][0]]) {
            if (insert(children[x][0], u, s, l, id[x])) {
                if (weight[children[x][0]] >= weight[x]) {
                    rebuild(children[x][0], l, id[x]);
                } else {
                    rotate(x, 0);
                    return true;
                }
            }
        } else {
            if (insert(children[x][1], u, s - size[children[x][0]] - 1, id[x], r)) {
                if (weight[children[x][1]] >= weight[x]) {
                    rebuild(children[x][1], id[x], r);
                } else {
                    rotate(x, 1);
                    return true;
                }
            }
        }
        update(x);
        return false;
    }
}

int get_rank(int &x, int u) {
    if (x == u) {
        return size[children[x][0]];
    }
    if (cmp(x, u)) {
        return size[children[x][0]] + 1 + get_rank(children[x][1], u);
    }
    return get_rank(children[x][0], u);
}

int main() {
    for (int i = 0; i < M; ++ i) {
        int l = 0;
        int r = M - 1;
        while (true) {
            includeOne[i].push_back(get_id(l, r));
            if (l == r) {
                break;
            }
            int m = l + r >> 1;
            if (i <= m) {
                r = m;
            } else {
                l = m + 1;
            }
        }
    }
    product(includeOne, include);
    for (int i = 0; i < M; ++ i) {
        int l = 0;
        int r = M - 1;
        while (l != r) {
            int m = l + r >> 1;
            if (i <= m) {
                excludeOne[i].push_back(get_id(m + 1, r));
                r = m;
            } else {
                excludeOne[i].push_back(get_id(l, m));
                l = m + 1;
            }
        }
    }
    product(excludeOne, exclude);
    size[N] = 0;
    weight[N] = INT_MAX;
    children[N][0] = children[N][1] = N;
    int q;
    while (scanf("%d", &q) == 1) {
        int last = 0;
        for (int i = 0; i < T * T * T; ++ i) {
            ds[i].clear();
        }
        int root = N;
        for (int i = 0; i < q; ++ i) {
            char op[2];
            int pos, v[4];
            scanf("%s", op);
            if (*op == '+') {
                scanf("%d", &pos);
                pos = (pos ^ last) - 1;
            }
            for (int i = 0; i < 4; ++ i) {
                scanf("%d", v + i);
                v[i] = (v[i] ^ last) - 1;
            }
            int encode = (v[0] * M + v[1]) * M + v[2];
            int d = v[3];
            if (*op == '+') {
                if (insert(root, i, pos, 0, INF)) {
                    rebuild(root, 0, INF);
                }
                for (int idx : include[encode]) {
                    ds[idx].insert(d, i);
                }
            } else {
                int min = N;
                int max = -1;
                for (int idx : exclude[encode]) {
                    int tmp = ds[idx].get_min(d);
                    if (cmp(tmp, min)) {
                        min = tmp;
                    }
                    tmp = ds[idx].get_max(d);
                    if (cmp(max, tmp)) {
                        max = tmp;
                    }
                }
                if (min == N) {
                    assert(max == -1);
                    last = 0;
                } else {
                    last = get_rank(root, max) - get_rank(root, min);
                }
                printf("%d\n", last);
            }
        }
    }
    return 0;
}
