#include <string>
#include <iostream>

using std::string;

std::string str;

void getNe(string &s, int &ne) {
	ne = 1;
	if (s[0] == '-') {
		s.assign(s.begin() + 1, s.end());
		ne = -1;
	}
	else if (s[0] == '+') 
		s.assign(s.begin() + 1, s.end());
}

void getRidPreZero(string &s) {
	int p = 0;
	while (s[p] == '0') p++;
	s.assign(s.begin() + p, s.end());
}

void getRidSufZero(string &s) {
	int d = 0;
	while (d < s.length() && s[d] != '.') d++;
	if (d == s.length()) return;
	int z = s.length() - 1;
	while (z > d && s[z] == '0') z--;
	if (z == d) s.assign(s.begin(), s.begin() + z);
	else s.assign(s.begin(), s.begin() + z + 1);
}

std::string s, t;
int nes, net;

void divStr() {
	int e = 0;
	while (str[e] != 'e') e++;
	s.assign(str.begin(), str.begin() + e);
	t.assign(str.begin() + e + 1, str.end());
}

int main() {
	std::cin >> str;
	divStr();
	getNe(s, nes);
	getNe(t, net);
	getRidPreZero(s);
	getRidPreZero(t);
	getRidSufZero(s);
	if (nes == -1)
		std::cout << '-';
	std::cout << s << "e";
	if (net == -1)
		std::cout << '-';
	if (t == "")
		std::cout << "0";
	std::cout << t << std::endl;
	return 0;
}