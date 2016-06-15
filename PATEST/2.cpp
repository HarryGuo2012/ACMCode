#include <iostream>
#include <string>

std::string A;

int h, m;
char d;

void output(int x) {
	for (int i = 0; i < x; i++)
		std::cout << "Dang";
	std::cout << std::endl;
}

int main() {
	std::cin >> A;
	h = (A[0] - '0') * 10 + A[1] - '0';
	m = (A[3] - '0') * 10 + A[4] - '0';
	if (h == 12 && m != 0) {
		output(1);
		return 0;
	}
	if (h <= 12) {
		std::cout << "Only " << A << ".  Too early to Dang." << std::endl;
		return 0;
	}
	if (m == 0) output(h - 12);
	else output(h + 1 - 12);
	return 0;
}