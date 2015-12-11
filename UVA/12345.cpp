#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cstdlib>
#include<set>
#include<climits>
#include<stack>
#include<cstdio>
#define MAX_N 50004
#define MAX_A 1000006
using namespace std;

int a[MAX_N];

struct Treap {
    stack<int> restNode;

    struct Node {
        int val, cnt, priority, size;
        int childs[2];

        Node() {
            memset(childs, 0, sizeof(childs));
            cnt = priority = 0;
            size = 0;
        }

        void set(int x) {
            val = x;
            cnt = 1;
            priority = rand();
            memset(childs, 0, sizeof(childs));
        }
    };

    int treapSize, treapCnt;
    vector<Node> tree;
    int root;

    Treap() { }

    Treap(int maxSize) {
        tree.resize(maxSize + 3);
        for (int i = 0; i < tree.size(); i++)tree[i] = Node();
        tree[0].priority = INT_MAX;
        root = 0;
        tree[0].size = 0;
        treapSize = treapCnt = 0;
        while (restNode.size())restNode.pop();
    }

    void pushUp(int v) {
        tree[v].size = tree[tree[v].childs[0]].size + tree[tree[v].childs[1]].size + tree[v].cnt;
    }

    void rotate(int &v, int d) {
        int t = tree[v].childs[d ^ 1];
        tree[v].childs[d ^ 1] = tree[t].childs[d];
        tree[t].childs[d] = v;
        pushUp(v);
        pushUp(t);
        v = t;
    }

    void __insert(int &v, int x) {
        if (!v) {
            if (restNode.size()) {
                v = restNode.top();
                restNode.pop();
            }
            else
                v = ++treapCnt;
            treapSize++;
            tree[v].set(x);
        }
        else if (tree[v].val == x) {
            tree[v].cnt++;
            treapSize++;
        }
        else {
            int t = (x > tree[v].val);
            __insert(tree[v].childs[t], x);
            if (tree[tree[v].childs[t]].priority < tree[v].priority)
                rotate(v, 1 ^ t);
        }
        pushUp(v);
    }

    void __erase(int &v, int x) {
        if (tree[v].val == x) {
            if (tree[v].cnt > 1)
                tree[v].cnt--, treapSize--;
            else {
                if (tree[v].childs[0] == 0 && tree[v].childs[1] == 0) {
                    restNode.push(v);
                    v = 0;
                    treapSize--;
                    return;
                }
                int t = tree[tree[v].childs[0]].priority < tree[tree[v].childs[1]].priority;
                rotate(v, t);
                __erase(v, x);
            }
        }
        else
            __erase(tree[v].childs[tree[v].val < x], x);
        pushUp(v);
    }

    int __getKth(int v, int k) {
        if (tree[tree[v].childs[0]].size >= k)
            return __getKth(tree[v].childs[0], k);
        k -= tree[tree[v].childs[0]].size;
        if (k <= tree[v].cnt)return tree[v].val;
        return __getKth(tree[v].childs[1], k - tree[v].cnt);
    }

    void insert(int x) {
        __insert(root, x);
    }

    void erase(int x) {
        __erase(root, x);
    }

    int getKth(int k) {
        return __getKth(root, k);
    }

    int getRank(int x) {
        if (getKth(1) >= x)return 0;
        int l = 1, r = treapSize + 1;
        while (r - l > 1) {
            int m = (l + r) >> 1;
            if (getKth(m) < x)l = m;
            else r = m;
        }
        return l;
    }

};

int N,M;

struct SegmentTree {
#define lchild L,m,v<<1
#define rchild m+1,R,v<<1|1

	struct Node {
		Treap tr;

		Node() { }

		Node(int trSize) {
			tr = Treap(trSize+1);
		}
	} tree[MAX_N*4];

	SegmentTree() { }

	void build(int L = 1, int R = N, int v = 1) {
		tree[v] = Node(R - L + 1);
		for (int i = L; i <= R; i++)
			tree[v].tr.insert(a[i]);
		if (L == R)return;
		int m = (L + R) >> 1;
		build(lchild);
		build(rchild);
	}

	void update(int i, int x, int L = 1, int R = N, int v = 1) {
		tree[v].tr.erase(a[i]);
		tree[v].tr.insert(x);
		if(L==R)return;
		int m = (L + R) >> 1;
		if (i <= m)update(i, x, lchild);
		if (i > m)update(i, x, rchild);
	}

	//change a[i] to x
	int query(int a, int b, int x, int L = 1, int R = N, int v = 1) {
		if (a <= L && R <= b)return tree[v].tr.getRank(x);
		int res = 0;
		int m = (L + R) >> 1;
		if (a <= m)res += query(a, b, x, lchild);
		if (b > m)res += query(a, b, x, rchild);
		return res;
	}
}seg;


set<int> se[MAX_A];
int num[MAX_N];

int getA(int i,int x){
	if(se[x].empty())return 0;
	set<int>::iterator it=se[x].lower_bound(i);
	if(it==se[x].begin())return 0;
	it--;
	return *it;
}

int main() {
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; i++) {
		int t;
		scanf("%d", &t);
		num[i] = t;
		se[t].insert(i);
	}
	for (int i = 1; i <= N; i++)
		a[i] = getA(i, num[i]);
	seg.build();
	while (M--) {
		char op[2];
		int x, y;
		scanf("%s %d%d", op, &x, &y);
		if (op[0] == 'M') {
			x++;
			seg.update(x, getA(x, y));
			set<int>::iterator it = se[y].lower_bound(x);
			if (it != se[y].end()){
				seg.update(*it, x);
				a[*it] = x;
			}
			a[x] = getA(x, y);
			se[num[x]].erase(x);
			num[x] = y;
			se[y].insert(x);
		}
		else
			printf("%d\n", seg.query(x + 1, y, x + 1));
	}
	return 0;
}

