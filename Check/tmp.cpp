#include <iostream>
#include <fstream>

int a[3], b[3];

int main() {
	int N, K;
	std::ofstream out("tmp.txt");
	std::cin >> N >> K;
	for (int i = 0; i < N; i++) {
		for (int i = 0; i < 3; i++)
			std::cin >> a[i];
		for (int i = 0; i < 3; i++)
			std::cin >> b[i];
		
		bool flag = 1;
		for (int i = 0; i < 3; i++)
			if (a[i] == b[i])
				flag = false;
		if (flag) {
			for (int i = 0; i < 3; i++)
				out << a[i] << " ";
			for (int i = 0; i < 3; i++)
				out << b[i] << " ";
			out << std::endl;
		}
	}
	return 0;
}