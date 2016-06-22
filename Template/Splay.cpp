#include <cstdio>

#define MAX_N 100005

struct node {
		int key, val;
		int child[2], father;
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

	void rotate(int x) {
		int p = Tree[x].father;
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

};

int main() {
	return 0;
}