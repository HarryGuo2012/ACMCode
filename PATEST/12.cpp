#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

#define MAX_N 12345

int N, M;
std::map<int, int> ma;
int val[MAX_N];
int tot = 0;

int tree[MAX_N];

int size = 0;

void Insert(int x) {
	tree[++size] = x;
	int pos = size;
	while (pos > 1) {
		int fa = pos >> 1;
		if (val[tree[fa]] > val[tree[pos]]) {
			std::swap(tree[fa], tree[pos]);
			pos = fa;
		}
		else break;
	}
}	

int Get(int x) {
	x = ma[x];
	for (int i = 1; i <= size; i++)
		if (tree[i] == x) return i;
}

int main() {
	std::cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		int a;
		std::cin >> a;
		ma[a] = ++tot;
		val[tot] = a;
		Insert(tot);
	}
	for (int i = 1; i <= M; i++) {
		int a, b;
		std::string s;
		std::cin >> a >> s;
		bool flag = false;
		if (s[0] == 'a') {
			std::cin >> b >> s >> s;
			int u = Get(a), v = Get(b);
			if ((u ^ v) == 1) flag = true;
		}
		else {
			std::cin >> s;
			if (s[0] == 'a') {
				std::cin >> s >> s >> b;
				int u = Get(a), v = Get(b);
				if (u / 2 == v) flag = true;
			}
			else {
				std::cin >> s;
				if (s[0] == 'r') {
					if (Get(a) == 1) flag = true;
				}
				else {
					std::cin >> s >> b;
					int u = Get(a), v = Get(b);
					if (v / 2 == u) flag = true;
				}
			}
		}
		if (flag) std::cout << "T" << std::endl;
		else std::cout << "F" << std::endl;
	}
	return 0;
}