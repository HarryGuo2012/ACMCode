#include <string>
#include <iostream>
#include <vector>
#include <fstream>

int T;
std::string s;
std::vector<char> vc;

int main(){
	std::ofstream out("B.txt");
	std::cin >> T;
	int cas = 0;
	while(T--){
		std::cin >> s;
		vc.clear();
		for(auto c : s)
			if(vc.size() == 0 || vc[vc.size() - 1] != c)
				vc.push_back(c);
		int ans = vc.size() - (vc[vc.size() - 1] == '+');
		out << "Case #" << ++cas << ": " << ans << std::endl;
	}
	return 0;
}