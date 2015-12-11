#include<iostream>
#include<cstring>
#include<vector>
#include<cstdio>
#include<algorithm>
using namespace std;

struct Treap{
	struct Node{
		int val,cnt,priority;
		Node(int v,int c,int p):v(val),cnt(c),priority(p){}
		Node(){}	
	};
	int size;
	vector<Node> tree;
	Treap(){}
	Treap(int maxSize){
		tree.resize(maxSize);
	}
};

int main(){
	return 0;
}
