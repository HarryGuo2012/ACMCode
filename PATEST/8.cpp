#include <iostream>

int N;

int main() {
	std::cin >> N;
	N--;
	N = (N + 2) % 7;
	std::cout << N + 1 << std::endl;
	return 0;
}