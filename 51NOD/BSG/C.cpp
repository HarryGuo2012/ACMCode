#include <cmath>
#include <iostream>
#include <iomanip>

int S;

const double pi = acos(-1);
const double eps = 1e-8;

double Get(double th) {
	double ct = cos(th);
	double Ls = S / (pi * (ct * ct + ct));
	return pi * Ls * sqrt(Ls) * ct * ct * sin(th) / 3;
}

int main() {
	std::cin >> S;
	double L = eps, R = pi / 2 - eps;
	/*
	for (int i = 0; i < 100; i++) {
		double m = (L + R) / 2;
		if (Get(m + eps) > Get(m)) L = m;
		else R = m;
	}
	*/
	
	for (int i = 0; i < 100; i++) {
		double m1 = L + (R - L) / 3;
		double m2 = R - (R - L) / 3;
		//printf("%.6f %.6f %.6f %.6f\n", m1, m2, Get(m1), Get(m2));
		if (Get(m1) < Get(m2))
			L = m1;
		else 
			R = m2;
	}
	
	std::cout << std::setprecision(7) << std::fixed << Get(R) << std::endl;
	return 0;
}