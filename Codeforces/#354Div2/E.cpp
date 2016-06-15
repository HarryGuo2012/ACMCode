#include <cstdio>
#include <complex>
#include <cmath>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

#define MaxN 100

const long long mod_v = 17ll * (1 << 27) + 1;
long long eps[MaxN], inv_eps[MaxN];
int tot;

long long power(long long x, long long p)
{
	long long v = 1;
	while(p)
	{
		if(p & 1) v = x * v % mod_v;
		x = x * x % mod_v;
		p >>= 1;
	}

	return v;
}

void init_eps(int n)
{
	tot = n;
	long long base = power(3, (mod_v - 1) / n);
	long long inv_base = power(base, mod_v - 2);
	eps[0] = 1, inv_eps[0] = 1;
	for(int i = 1; i < n; ++i)
	{
		eps[i] = eps[i - 1] * base % mod_v;
		inv_eps[i] = inv_eps[i - 1] * inv_base % mod_v;
	}
}

long long inc(long long x, long long d) 
{
	x += d; 
	return x >= mod_v ? x - mod_v : x; 
}

long long dec(long long x, long long d) 
{
	x -= d; 
	return x < 0 ? x + mod_v : x; 
}

void transform(int n, long long *x, long long *w)
{
	for(int i = 0, j = 0; i != n; ++i)
	{
		if(i > j) std::swap(x[i], x[j]);
		for(int l = n >> 1; (j ^= l) < l; l >>= 1);
	}

	for(int i = 2; i <= n; i <<= 1)
	{
		int m = i >> 1;
		for(int j = 0; j < n; j += i)
		{
			for(int k = 0; k != m; ++k)
			{
				long long z = x[j + m + k] * w[tot / i * k] % mod_v;
				x[j + m + k] = dec(x[j + k], z);
				x[j + k] = inc(x[j + k], z);
			}
		}
	}
}

void polynomial_inverse(int deg, long long* a, long long* b, long long* tmp)
{
	if(deg == 1)
	{
		b[0] = power(a[0], mod_v - 2);
	} else {
		polynomial_inverse((deg + 1) >> 1, a, b, tmp);

		int p = 1;
		while(p < deg << 1) p <<= 1;
		copy(a, a + deg, tmp);
		fill(tmp + deg, tmp + p, 0);
		transform(p, tmp, eps);
		transform(p, b, eps);
		for(int i = 0; i != p; ++i)
		{
			b[i] = (2 - tmp[i] * b[i] % mod_v) * b[i] % mod_v;
			if(b[i] < 0) b[i] += mod_v;
		}
		transform(p, b, inv_eps);
		long long inv = power(p, mod_v - 2);
		for(int i = 0; i != p; ++i)
			b[i] = b[i] * inv % mod_v;
		fill(b + deg, b + p, 0);

	}
}

#define inverse_transform transform
long long A0[MaxN], B0[MaxN], tmp0[MaxN];

void polynomial_division(int n, int m, long long *A, long long *B, long long *D, long long *R)
{

	int p = 1, t = n - m + 1;
	while(p < t << 1) p <<= 1;

	fill(A0, A0 + p, 0);
	fill(tmp0, tmp0 + p, 0);
	reverse_copy(B, B + m, A0);
	polynomial_inverse(t, A0, B0, tmp0);
	fill(B0 + t, B0 + p, 0);
	transform(p, B0, eps);

	reverse_copy(A, A + n, A0);
	fill(A0 + t, A0 + p, 0);
	transform(p, A0, eps);

	for(int i = 0; i != p; ++i)
		A0[i] = A0[i] * B0[i] % mod_v;
	inverse_transform(p, A0, inv_eps);
	reverse(A0, A0 + t);
	copy(A0, A0 + t, D);

	for(p = 1; p < n; p <<= 1);
	fill(A0 + t, A0 + p, 0);
	transform(p, A0, eps);
	copy(B, B + m, B0);
	fill(B0 + m, B0 + p, 0);
	transform(p, B0, inv_eps);
	for(int i = 0; i != p; ++i)
		A0[i] = A0[i] * B0[i] % mod_v;
	inverse_transform(p, A0, inv_eps);
	for(int i = 0; i != m; ++i)
		R[i] = (A[i] - A0[i]) % mod_v;
	fill(R + m, R + p, 0);
}

int kk;
long long P[MaxN], Q[MaxN], D[MaxN], R[MaxN];

string ts;

int main()
{
	init_eps(2048);
	int n;
	std::cin >> n >> kk;
	Q[0] = -kk;
	Q[1] = 1;
	for(int i = 0; i != n; ++i) {
		std::string ts;
		std::string::size_type sz;
		cin >> ts;
		if (ts == "?") P[i] = rand() % 100 - 50;
		else P[i] = stoi(ts,&sz);
	}
	polynomial_division(n, 3, P, Q, D, R);
	bool flag = true;
	for (int i = 0; i < n; i++)
		if (R[i] != 0) 
			flag = false;
	if (flag) printf("Yes\n");
	else printf("No\n");
	return 0;
}