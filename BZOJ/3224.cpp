#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cstdlib>
#include<set>
#include<climits>
#include<stack>
#include<cstdio>
#define MAX_N 105004
#define MAX_A 1050006
using namespace std;

const int inf=INT_MAX-5;

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
            cnt = size = 1;
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
		tree[t].size=tree[v].size;
        pushUp(v);
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
			return;
        }
		tree[v].size++;
        if (tree[v].val == x) {
            tree[v].cnt++;
            treapSize++;
        }
        else {
            int t = (x > tree[v].val);
            __insert(tree[v].childs[t], x);
            if (tree[tree[v].childs[t]].priority < tree[v].priority)
                rotate(v, 1 ^ t);
        }
    }

    void __erase(int &v, int x) {
        if (tree[v].val == x) {
            if (tree[v].cnt > 1)
                tree[v].cnt--, treapSize--,tree[v].size--;
            else {
                if (tree[v].childs[0] == 0 || tree[v].childs[1] == 0) {
                    restNode.push(v);
                    v = tree[v].childs[0]+tree[v].childs[1];
                    treapSize--;
                    return;
                }
                int t = tree[tree[v].childs[0]].priority < tree[tree[v].childs[1]].priority;
                rotate(v, t);
                __erase(v, x);
            }
        }
        else{
            __erase(tree[v].childs[tree[v].val < x], x);
			tree[v].size--;
		}
    }

    int __getKth(int v, int k) {
        if (tree[tree[v].childs[0]].size >= k)
            return __getKth(tree[v].childs[0], k);
        k -= tree[tree[v].childs[0]].size;
        if (k <= tree[v].cnt)return tree[v].val;
        return __getKth(tree[v].childs[1], k - tree[v].cnt);
    }

    int __getPre(int v, int x) {
        if (v == 0)return -inf;
        if (tree[v].val >= x)return __getPre(tree[v].childs[0], x);
        if (tree[v].childs[1])return max(tree[v].val, __getPre(tree[v].childs[1], x));
        return tree[v].val;
    }

    int __getNext(int v, int x) {
        if (v == 0)return inf;
        if (tree[v].val <= x)return __getNext(tree[v].childs[1], x);
        if (tree[v].childs[0])return min(tree[v].val, __getNext(tree[v].childs[0], x));
        return tree[v].val;
    }

	int __getRank(int v,int x){
		if(v==0)return 0;
		if(tree[v].val<x)return tree[v].cnt+tree[tree[v].childs[0]].size+__getRank(tree[v].childs[1],x);
		else return __getRank(tree[v].childs[0],x);
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

    int getRank(int x) {//How many numbers are less than x
      	 __getRank(root,x);
    }

    int getPre(int x) {
        return __getPre(root, x);
    }

    int getNext(int x) {
        return __getNext(root, x);
    }

};


int x;
int n;

Treap treap(100005);

int main(){
    scanf("%d",&n);
    while(n--){
        int op;
        scanf("%d%d",&op,&x);
        switch(op){
            case 1:
                treap.insert(x);
                break;
            case 2:
                treap.erase(x);
                break;
            case 3:
                printf("%d\n",treap.getRank(x)+1);
                break;
            case 4:
                printf("%d\n",treap.getKth(x));
                break;
            case 5:
                printf("%d\n",treap.getPre(x));
                break;
            case 6:
                printf("%d\n",treap.getNext(x));
                break;
        }
    }
    return 0;
}


