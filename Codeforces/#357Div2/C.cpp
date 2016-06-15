#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <functional>

struct node {
	std::string s;
	int val;
	node(std::string ss, int vv) : s(ss), val(vv) {}
	node() {}
};

std::vector<node> v;
int n;

std::priority_queue<int, std::vector<int>, std::greater<int> > que;

int main() {
	std::cin.sync_with_stdio(false);
	std::cin >> n;
	for (int i = 0; i < n; i++) {
		node t;
		std::cin >> t.s;
		if (t.s[0] != 'r') std::cin >> t.val;
		if (t.s[0] == 'i') {
			que.push(t.val);
			v.push_back(t);
		}
		if (t.s[0] == 'r') {
			if (que.size() == 0)
				v.push_back(node("insert", 0));
			else
				que.pop();
			v.push_back(t);
		}
		if (t.s[0] == 'g') {
			while (que.size() && que.top() < t.val) {
				v.push_back(node("removeMin", 0));
				que.pop();
			}
			if (que.empty() || que.top() != t.val) {
				v.push_back(node("insert", t.val));
				que.push(t.val);
			}
			v.push_back(t);
		}
	}
	std::cout << v.size() << std::endl;
	for (auto u : v) {
		std::cout << u.s << " ";
		if (u.s[0] != 'r')
			std::cout << u.val;
		std::cout << std::endl;
	}
	return 0;
}