#include <iostream>
#include <algorithm>
#include <complex>
#include <cmath>
#include <cstring>
#include <string>

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

std::complex<double> A[MAX_N], B[MAX_N];
std::string a, b;

int ans[MAX_N];

int main() {
	while (std::cin >> a >> b) {

		memset(ans, 0, sizeof(ans));
		memset(A, 0, sizeof(A));
		memset(B, 0, sizeof(B));
		memset(unitRoot, 0, sizeof(unitRoot));
		memset(artiUnitRoot, 0, sizeof(artiUnitRoot));

		bool neg = false;

		if (a[0] == '-' && b[0] == '-') {
			a.assign(a.begin() + 1, a.end());
			b.assign(b.begin() + 1, b.end());
		}
		else if (a[0] == '-') {
			neg = true;
			a.assign(a.begin() + 1, a.end());
		}
		else if (b[0] == '-') {
			neg = true;
			b.assign(b.begin() + 1, b.end());
		}

		if (a[0] == '0' || b[0] == '0') {
			std::cout << 0 << std::endl;
			continue;
		}

		std::reverse(a.begin(), a.end());
		std::reverse(b.begin(), b.end());
		for (int i = 0; i < a.length(); i++)
			A[i] = a[i] - '0';
		for (int i = 0; i < b.length(); i++)
			B[i] = b[i] - '0';
		int n = std::max(a.length(), b.length()), _n = 1;
		while (_n < n) _n <<= 1;
		_n <<= 1;
		initUnitRoot(_n);
		transform(_n, A, unitRoot);
		transform(_n, B, unitRoot);
		for (int i = 0; i < _n; i++)
			A[i] = A[i] * B[i];
		transform(_n, A, artiUnitRoot);
		for (int i = 0; i < a.length() + b.length() - 1; i++) {
			ans[i] += (int)(A[i].real() / _n + 0.5);
			ans[i + 1] = ans[i] / 10;
			ans[i] %= 10;
		}
		if (neg) std::cout << '-';
		if (ans[a.length() + b.length() - 1] != 0) std::cout << ans[a.length() + b.length() - 1];
		for (int i = a.length() + b.length() - 2; i >= 0; i--)
			std::cout << ans[i];
		std::cout << std::endl;
	}
	return 0;
}