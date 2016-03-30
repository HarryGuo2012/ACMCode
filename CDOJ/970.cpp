#include <string>
#include <iostream>
#include <cstdio>

int T;
std::string s;

int main(){
	std::cin >> T;
	while(T--){
		std::cin >> s;
		int t = std::stoi(s, nullptr, 2);
		printf("%d %o\n", t, t);
	}
	return 0;
}