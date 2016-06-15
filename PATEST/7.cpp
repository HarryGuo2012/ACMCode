#include <iostream>
#include <string>

std::string s;

int G, P, L, T;

int main() {
	std::cin >> s;
	for (int i = 0; i < s.length(); i++) {
		G += (s[i] == 'G') + (s[i] == 'g');
		P += (s[i] == 'P') + (s[i] == 'p');
		L += (s[i] == 'L') + (s[i] == 'l');
		T += (s[i] == 'T') + (s[i] == 't');
	}
	while (G || P || L || T) {
		if (G) {
			std::cout << 'G';
			G--;
		}
		if (P) {
			std::cout << 'P';
			P--;
		}
		if (L) {
			std::cout << 'L';
			L--;
		}
		if (T) {
			std::cout << 'T';
			T--;
		}
	}
	std::cout << std::endl;
	return 0;
}