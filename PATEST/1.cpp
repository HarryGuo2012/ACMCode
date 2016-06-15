#include <iostream>
#include <string>
#include <iomanip>

std::string s;

int main() {
	std::cin >> s;
	double ne = 1;
	int cnt = 0;
	if (s[0] == '-') ne = 1.5;
	if ((s[s.length() - 1] - '0') % 2 == 0) ne = ne * 2;
	for (int i = 0; i < s.length(); i++) 
		cnt += (s[i] == '2');
	if (s[0] == '-') std::cout << std::setprecision(2) << std::fixed << cnt * ne / (s.length() - 1) * 100 << '%' << std::endl;
	else std::cout << std::setprecision(2) << std::fixed << cnt * ne / s.length() * 100 << '%' << std::endl;
	return 0;
}