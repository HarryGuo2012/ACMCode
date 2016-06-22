#include <iostream>
#include <cstdlib>
#include <ctime>
#include <bitset>
#include <cmath>
#include <string>

#define N 5000

const double r = 0.98;

using std::bitset;

bitset<N> bit, one;

void init() {
	one = 1;
	srand(time(0));
	for (int i = 0; i < 5000; i++)
		bit[i] = rand() % 2;
}

void output(bitset<N> b) {
	std::cout << b.to_string<char, std::string::traits_type, std::string::allocator_type>() << std::flush << std::endl;
}

bitset<N> inv(int x) {
	bitset<N> tmp = bit;
	for (int i = 0; i < x; i++) tmp[i] = bit[i] ^ 1;
	return tmp;
}

double Energy(bitset<N> b) {
	output(b);
	double res;
	std::cin >> res;
	return -res;
}

double drand() {
	return rand() % 10000 / 10000.0;
}

void SimulatedAnnealing() {
	double Te = N, E = 0;
	for (int tim = 0; tim < 100; tim++) {
		bitset<N> bitNei = inv(Te);
		double nE = Energy(bitNei);
		double dE = nE - E;
		if (dE < 0 || drand() < exp(-dE / Te)) {
			bit = bitNei;
			E = nE;
		}
		Te *= r;
	}
}

int main() {
	std::cin.sync_with_stdio(false);
	init();
	SimulatedAnnealing();
	return 0;
}