#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <tuple>
#include <utility>
#include <vector>

struct Node;

struct Point {
    Point() {}

    Point(int x, int y) : x(x), y(y) {}

    Point& operator += (const Point &o) {
        x += o.x;
        y += o.y;
        return *this;
    }

    int x, y;
};

bool operator == (const Point &a, const Point &b) {
    return a.x == b.x && a.y == b.y;
}

Point operator + (Point a, const Point &b) {
    return a += b;
}

int det(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}

std::ostream& operator << (std::ostream &out, const Point &p) {
    return out << "(" << p.x << "," << p.y << ")";
}

Node *null_false, *null_true;

struct Node {
    Node* update() {
        parent = null_false;
        size = left->size + 1 + right->size;
        sum = left->sum + weight + right->sum;
        left->parent = right->parent = this;
        return this;
    }

    bool null() const {
        return this == null_false || this == null_true;
    }

    void take(int n, Node*& l, Node*& r) {
        if (null()) {
            l = r = null_false;
            return;
        }
        if (n <= left->size) {
            left->take(n, l, left);
            r = update();
        } else {
            right->take(n - 1 - left->size, right, r);
            l = update();
        }
    }

    Node* up() {
        Node* p = this;
        while (!p->parent->null()) {
            p = p->parent;
        }
        return p;
    }

    int rank() const {
        int result = left->size;
        const Node* p = this;
        while (!p->parent->null()) {
            if (p->parent->right == p) {
                result += p->parent->left->size + 1;
            }
            p = p->parent;
        }
        return result;
    }

    int size, weight, sum;
    Node* parent;
    Node* left;
    Node* right;
};

bool random(int a, int b) {
    return rand() % (a + b) < a;
}

Node* concat(Node* u, Node* v) {
    if (u->null()) {
        return v;
    }
    if (v->null()) {
        return u;
    }
    if (random(u->size, v->size)) {
        u->right = concat(u->right, v);
        return u->update();
    }
    v->left = concat(u, v->left);
    return v->update();
}

const int N = 201;
const int V = (N + 1) * (N + 1) * 4;

const Point DELTA[] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

char buffer[N + 3];
int n, m, board[N + 2][N + 2];
Node nodes[V];

std::ostream& operator << (std::ostream &out, const Node &n) {
    if (n.null()) {
        return out;
    }
    return out << "(" << &n - nodes << *n.left << *n.right << ")";
}

int vertex_id(const Point &p) {
    return p.x * (m + 1) + p.y;
}

int edge_id(const Point &p, int d) {
    return p.x * (m + 1) + p.y << 2 | d;
}

void decode(int id, Point &p, int &d) {
    d = id & 3;
    id >>= 2;
    p = {id / (m + 1), id % (m + 1)};
}

#define DECODE(id) Point p; int d; decode(id, p, d)

int mirror(int id) {
    DECODE(id);
    p += DELTA[d];
    d ^= 2;
    return edge_id(p, d);
}

int get_board(const Point &p) {
    return board[p.x][p.y];
}

Point left_hand(int id) {
    static const Point DELTA[] = {{0, 0}, {1, 0}, {1, 1}, {0, 1}};

    DECODE(id);
    return p += DELTA[d];
}

Point right_hand(int id) {
    return left_hand(mirror(id));
}

bool has_edge(int x, int y, int d) {
    int id = edge_id({x, y}, d);
    return get_board(left_hand(id)) != get_board(right_hand(id));
}

int next_edge(int id) {
    DECODE(mirror(id));
    do {
        d = d + 1 & 3;
    } while (!has_edge(p.x, p.y, d));
    return edge_id(p, d);
}

int prev_edge(int id) {
    DECODE(id);
    do {
        d = d + 3 & 3;
    } while (!has_edge(p.x, p.y, d));
    return mirror(edge_id(p, d));
}

void init_node(int id) {
    DECODE(id);
    nodes[id].weight = det(p, p + DELTA[d]);
    nodes[id].parent = nodes[id].left = nodes[id].right = null_false;
    nodes[id].update();
}

int component;

void link(int a, int b) {
    Node *u = nodes[a].up();
    Node *v = nodes[b].up();
    if (u == v) {
        u->parent = null_true;
        component += u->sum < 0;
    } else {
        concat(u, v);
    }
}

void unlink(int a) {
    Node* p = nodes[a].up();
    Node* backup = p->parent;
    if (backup == null_true) {
        p->parent = null_false;
        component -= p->sum < 0;
    }
    int s = nodes[a].rank() + 1;
    if (s != p->size) {
        Node *u, *v;
        p->take(s, u, v);
        if (backup == null_true) {
            concat(v, u);
        }
    }
}

std::vector<int> get_nexts(const std::vector<int> &edges) {
    std::vector<int> result;
    for (auto &&e : edges) {
        DECODE(e);
        result.push_back(has_edge(p.x, p.y, d) ? next_edge(e) : -1);
    }
    return result;
}

int main() {
    null_false = new Node();
    null_true = new Node();
    null_false->size = null_true->size = null_false->size = null_true->size = 0;
    null_false->parent = null_false->left = null_false->right = null_false;
    null_true->parent = null_true->left = null_true->right = null_true;
    int q;
    scanf("%d%d%d", &n, &m, &q);
    memset(board, -1, sizeof(board));
    for (int i = 1; i <= n; ++ i) {
        scanf("%s", buffer + 1);
        for (int j = 1; j <= m; ++ j) {
            board[i][j] = buffer[j] == '1';
        }
    }
    for (int i = 0; i <= n; ++ i) {
        for (int j = 0; j <= m; ++ j) {
            for (int k = 0; k < 4; ++ k) {
                init_node(edge_id({i, j}, k));
            }
        }
    }
    component = 0;
    for (int i = 0; i <= n; ++ i) {
        for (int j = 0; j <= m; ++ j) {
            for (int k = 0; k < 4; ++ k) {
                int id = edge_id({i, j}, k);
                if (has_edge(i, j, k)) {
                    link(id, next_edge(id));
                }
            }
        }
    }
    int last = component;
    while (q --) {
        int x, y;
        scanf("%d%d", &x, &y);
        x ^= last;
        y ^= last;
        std::vector<int> edges;
        for (int i = x - 1; i <= x; ++ i) {
            for (int j = y - 1; j <= y; ++ j) {
                for (int k = 0; k < 4; ++ k) {
                    edges.push_back(mirror(edge_id({i, j}, k)));
                }
            }
        }
        std::vector<int> old_next = get_nexts(edges);
        board[x][y] ^= 1;
        std::vector<int> new_next = get_nexts(edges);
        for (int i = 0; i < (int)edges.size(); ++ i) {
            if (old_next[i] != new_next[i] && old_next[i] != -1) {
                unlink(edges[i]);
            }
        }
        for (int i = 0; i < (int)edges.size(); ++ i) {
            if (old_next[i] != new_next[i] && new_next[i] != -1) {
                link(edges[i], new_next[i]);
            }
        }
        printf("%d\n", last = component);
    }
    return 0;
}
