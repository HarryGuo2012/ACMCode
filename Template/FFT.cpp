#include <cstdio>
#include <algorithm>
#include <complex>
#include <cmath>

//MAX_N should lager than n which is exploded to a power of 2
#define MAX_N 300005

const double pi = acos(-1);

std::complex<double> unitRoot[MAX_N], artiUnitRoot[MAX_N];

void initUnitRoot(int n) {
	for (int i = 0; i < n; i++) {
		unitRoot[i] = std::complex<double>(cos(2.0 * pi * i / n), sin(2.0 * pi * i / n));
		artiUnitRoot[i] = std::conj(unitRoot[i]);
	}
}

void bitReverse(int n, std::complex<double> *x) {
	for(int i = 0, j = 0; i != n; ++i) {
		if(i > j) std::swap(x[i], x[j]);
		for(int l = n >> 1; (j ^= l) < l; l >>= 1);
	}
}

//FFT use transform(n, x, unitRoot)
//IFFT use transform(n, x, artiUnitRoot)

void transform(int n, std::complex<double> *x, std::complex<double> *w) {
	bitReverse(n, x);
	for(int i = 2; i <= n; i <<= 1) 
		for(int j = 0, m = i >> 1; j < n; j += i) 
			for(int k = 0; k != m; ++k) {
				std::complex<double> z = x[j + m + k] * w[n / i * k];
				x[j + m + k] = x[j + k] - z;
				x[j + k] += z;
			}
}

int main() {
	return 0;
}