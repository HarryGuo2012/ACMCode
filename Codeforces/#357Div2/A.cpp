#include <string>
#include <iostream>

int main() {
	std::string s;
	int a, b;
	int n;
	std::cin >> n;
	bool flag = false;
	while (n--) {
		std::cin >> s >> a >> b;
		if (a >= 2400 && b > a) flag = true;
	}
	if (flag) std::cout << "YES" << std::endl;
	else std::cout << "NO" << std::endl;
	return 0;
}