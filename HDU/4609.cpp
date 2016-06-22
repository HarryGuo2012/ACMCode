#include <cstdio>
#include <algorithm>
#include <complex>
#include <cmath>
#include <vector>

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

int n = 1 << 18;

std::complex<double> A[MAX_N];
std::vector<int> v;

int main() {
	initUnitRoot(n);
	int T;
	scanf("%d", &T);
	while (T--) {
		v.clear();
		double ans = 0;
		for (int i = 0; i < MAX_N; i++) A[i] = 0;
		int N;
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			int a;
			scanf("%d", &a);
			v.push_back(a);
			A[a] = A[a] + 1.0;
		}
		transform(n, A, unitRoot);
		for (int i = 0; i < MAX_N; i++)
			A[i] = A[i] * A[i];
		transform(n, A, artiUnitRoot);
		std::sort(v.begin(), v.end());
		for (int i = 0; i < MAX_N; i++) 
			if (A[i].real() > 0.5) {
				//printf("%d %.5f\n", i, A[i].real() / n);
				ans += A[i].real() / n * (v.end() - std::lower_bound(v.begin(), v.end(), i));
			}
		for (int i = 0; i < v.size(); i++) {
			int u = v[i] * 2;
			ans -= (v.end() - std::lower_bound(v.begin(), v.end(), u));
		}
		//printf("%.4f\n", ans);
		ans = (double) N * (N - 1) * (N - 2) - ans * 3;
		ans /= N * (N - 1) * (N - 2.0);
		printf("%.7f\n", ans);
	}
	return 0;
}