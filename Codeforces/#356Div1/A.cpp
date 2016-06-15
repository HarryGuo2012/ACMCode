#include <iostream>
#include <string>
#define MAX_N 123
using namespace std;

int prime[MAX_N], tot = 0;
bool check[MAX_N];

void Euler() {
	for (int i = 2; i < MAX_N; i++) {
		if (!check[i]) prime[++tot] = i;
		for (int j = 1; j <= tot; j++) {
			if (i * prime[j] >= MAX_N) break;
			check[i * prime[j]] = 1;
			if (i % prime[j] == 0) break;
		}
	}
}

bool Ask(int x) {
	std::cout << x << std::flush << std::endl;
	std::string s;
	std::cin >> s;
	return s == "yes";
}

bool d[MAX_N];
bool dd[MAX_N];
int main() {
	Euler();
	for (int i = 1; i <= 15; i++)
		d[i] = Ask(prime[i]);
	for (int i = 1; i <= 4; i++)
		dd[i] = Ask(prime[i] * prime[i]);
	int cnt = 0;
	for (int i = 1; i <= 15; i++)
		cnt += d[i];
	bool flag = false;
	for (int i = 1; i <= 4; i++)
		flag |= d[i];
	if (cnt > 1) {
		std::cout << "composite" << std::endl;
		return 0;
	}
	if (cnt == 0) {
		std::cout << "prime" << std::endl;
		return 0;
	}
	if ((!flag) && cnt <= 1) {
		std::cout << "prime" << std::endl;
		return 0;
	}
	int p = 1;
	while (d[p] == 0) p++;
	if (dd[p])
		std::cout << "composite" << std::endl;
	else
		std::cout << "prime" << std::endl;
	return 0;
}