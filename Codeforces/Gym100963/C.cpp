#include <iostream>
#include <string>

std::string s;

int Get(int L, int R) {
	int res = 0;
	for (int i = L; i <= R; i++) 
		res = res * 10 + (s[i] - '0');
	return res;
}

int main() {
	while (std::cin >> s) {
		int p = 0, i = 0, now;
		bool first = true;
		char op = ' ';
		while (i < s.length()) {
			if (s[i] < '0' || s[i] > '9') {
				int tmp = Get(p, i - 1);
				if (tmp > 9999 || tmp < 0) {
					std::cout << "E" << std::endl;
					break;
				}
				if (first) {
					now = tmp;
					first = false;
				}
				else {
					if (op == '+') now = now + tmp;
					if (op == '-') now = now - tmp;
					if (op == '*') now = now * tmp;
				}
				if (now > 9999 || now < 0) {
					std::cout << "E" << std::endl;
					break;
				}
				op = s[i];
				if (op == '=') {
					std::cout << now << std::endl;
					break;
				}
				p = i + 1;
			}
			i++;
		}
	}
	return 0;
}