#include <cstdio>
#include <cstring>
#include <map>
#include <queue>
#include <vector>

struct Node {
    Node *left;
    Node *right;

    Node(Node *left, Node *right) : left(left), right(right) {}

    long  at(int, int, int);
    Node* insert(int, int, int, long);
};

Node* null;

long Node::at(int l, int r, int k) {
    if (this == null) {
        return 0;
    }
    if (l == r) {
        return (long)(left);
    }
    int m = l + r >> 1;
    return k <= m ? left->at(l, m, k) : right->at(m + 1, r, k);
}

Node* Node::insert(int l, int r, int k, long v) {
    if (k < l || r < k) {
        return this;
    }
    if (l == r) {
        return new Node((Node*)v, null);
    }
    int m = l + r >> 1;
    return new Node(left->insert(l, m, k, v), right->insert(m + 1, r, k, v));
}

Node* update(int n, Node *r, const std::map<int, int> &children) {
    for (const auto &it : children) {
        r = r->insert(1, n, it.first, it.second);
    }
    return r;
}

int main() {
    int n;
    scanf("%d", &n);
    std::vector<int> parent(n + 1);
    for (int i = 1; i <= n; ++ i) {
        scanf("%d", &parent[i]);
    }
    std::vector<std::map<int, int>> children(n + 1);
    for (int i = 1; i <= n; ++ i) {
        int c;
        scanf("%d", &c);
        children[parent[i]][c] = i;
    }
    null = new Node(NULL, NULL);
    null->left = null->right = null;
    std::vector<int>   fail(n + 1);
    std::vector<Node*> transfer(n + 1);
    transfer[0] = update(n, null, children[0]);
    std::queue<int> queue;
    for (const auto &it : children[0]) {
        int v = it.second;
        fail[v] = 0;
        queue.push(v);
    }
    while (!queue.empty()) {
        int u = queue.front();
        queue.pop();
        transfer[u] = update(n, transfer[fail[u]], children[u]);
        for (const auto &it : children[u]) {
            int v = it.second;
            fail[v] = transfer[fail[u]]->at(1, n, it.first);
            queue.push(v);
        }
    }
    for (int i = 1; i <= n; ++ i) {
        printf("%d%c", fail[i], " \n"[i == n]);
    }
    return 0;
}
