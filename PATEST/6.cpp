#include <iostream>

int a, b;
int main() {
	int n;
	std::cin >> n;
	for (int i = 0; i < n; i++) {
		int x;
		std::cin >> x;
		if (x & 1) a++;
		else b++;
	}
	std::cout << a << " " << b << std::endl;
	return 0;
}