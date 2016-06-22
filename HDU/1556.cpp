#include <cstdio>
#include <cstring>

#define MAX_N 100005

struct node {
		int key, val;
		node (int k, int v) : key(k), val(v) {}
		node () {}
		int child[2], father;
		int lazy;
}Tree[MAX_N];
int nodeTot = 0;

struct SplayTree {
	int root;
	SplayTree() {root = 0;}
	bool son(int x) {
		return x == Tree[Tree[x].father].child[1];
	}

	void point (int x, int y, bool s) {
		Tree[x].child[s] = y;
		Tree[y].father = x;
	}

	void pushDown(int x) {
		for (int i = 0; i < 2; i++) {
			Tree[Tree[x].child[i]].val += x;
			Tree[Tree[x].child[i]].lazy += x;
		}
		Tree[x].lazy = 0;
	}

	void rotate(int x) {
		int p = Tree[x].father;
		pushDown(p);
		pushDown(x);
    	bool s = son(x);
   		point(Tree[p].father, x, son(p));
    	point(p, Tree[x].child[s ^ 1], s);
    	point(x, p, s ^ 1);
	}

	void splay(int x) {
		while (Tree[x].father) {
			if (Tree[Tree[x].father].father != 0) 
				rotate(son(x) == son(Tree[x].father) ? Tree[x].father : x);
			rotate(x);
		}
		root = x;
	}

	void insert(node u) {
		int x = root, p = 0;
		while (x) {
			p = x;
			x = Tree[x].child[u.key > Tree[x].key];
		}
		Tree[++nodeTot] = u;
		point(p, nodeTot, u.key > Tree[p].key);
		splay(nodeTot);
	}

	void update(int l, int r, int x) {
		splay(r + 1);
		splay(l - 1);
		int u = Tree[Tree[root].child[1]].child[0];
		Tree[u].lazy += x;
		Tree[u].val += x;
	}

	void output(int x) {
		if (x == 0) return;
		pushDown(x);
		output(Tree[x].child[0]);
		printf("%d ", Tree[x].val);
		output(Tree[x].child[1]);
	}

};

SplayTree splayTree;
int n;

int main() {
	while (true) {
		scanf("%d", &n);
		if (n == 0) break;
		memset(Tree, 0, sizeof(Tree));
		splayTree.root = 0;
		for (int i = 1; i <= n; i++) splayTree.insert(node(i, 0));
		for (int i = 1; i <= n; i++) {
			int a, b;
			scanf("%d%d", &a, &b);
			splayTree.update(a, b, 1);
		}
		splayTree.output(splayTree.root);
		printf("\n");
	}
	return 0;
}