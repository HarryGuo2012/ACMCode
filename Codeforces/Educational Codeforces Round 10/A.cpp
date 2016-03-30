#include <iostream>

int h1, h2, a, b;

int main(){
	std::cin >> h1 >> h2 >> a >> b;
	int hour = 2;
	bool am = false;
	for(int t = 0; t < 1e5 * 24 * 5; t++){
		if(h1 >= h2){
			if(t < 20) std::cout << 0 << std::endl;
			else std::cout << (t - 20) / 24 + 1 << std::endl;
			return 0;
		}
		if(am && hour >= 10)
			h1 += a;
		if((!am) && hour < 10)
			h1 += a;
		if(am && hour < 10)
			h1 -= b;
		if((!am) && hour >= 10)
			h1 -= b;
		hour++;
		if(hour == 13)
			hour = 1, am ^= 1;
		//std::cout << h1 << std::endl;
	}
	std::cout << -1 << std::endl;
	return 0;
}