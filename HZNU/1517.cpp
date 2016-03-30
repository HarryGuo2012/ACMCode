#include <iostream>

int cnt(long long x){
	int res = 0;
	while(x){
		res += x & 1;
		x >>= 1;
	}
	return res;
}

int main(){
	long long n;
	while(std::cin >> n){
		std::cout << cnt(n) << std::endl;
	}
	return 0;
}