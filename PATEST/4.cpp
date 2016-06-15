#include <string>
#include <set>
#include <iostream>

std::set<std::string> se;
std::set<std::string> ss;
int N;

int main() {
	std::cin >> N;
	for (int i = 0; i < N; i++) {
		int K;
		std::cin >> K;
		for (int i = 0; i < K; i++) {
			std::string s;
			std::cin >> s;
			if (K > 1) se.insert(s);
		}
	}
	int M;
	std::cin >> M;
	bool first = true;
	for (int i = 0; i < M; i++) {
		std::string s;
		std::cin >> s;
		if (se.find(s) == se.end() && ss.find(s) == ss.end()) {
			ss.insert(s);
			if (first) {
				std::cout << s;
				first = false;
			}
			else
				std::cout << " " << s;
		}
	}
	if (ss.size() == 0)
		std::cout << "No one is handsome";
	std::cout << std::endl;
	return 0;
}