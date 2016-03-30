#include <iostream>
#include <cstdlib>
#include <ctime>

int main(){
	srand(time(0));
	int N = rand() % 10 + 1, Q = rand() % 10 + 1;
	std::cout << N << " " << Q << std::endl;
	for(int i = 1; i <= N; i++)
		std::cout << rand() % 10 + 1 << " ";
	std::cout << std::endl;
	for(int i = 1; i <= Q; i++){
		int t = rand() % 2 + 1;
		std::cout << t << " ";
		if(t == 1)
			std::cout << rand() % N + 1 << " " << rand() % 10 + 1 << std::endl;
		else
			std::cout << rand() % N + 1 << " " << std::endl;
	}
	return 0;
}