/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 *
 * Time = 50 * (80000 + 5000*(16+gcd) + 16*log*mul)
 */

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long long ll;
typedef long double dbl;
	
const int M = 1e6 + 1; // pow(1e18, 1./3)

ll m;
int pn, p[M];

inline void Mul( ll &a, ll b ) {
	ll k = (dbl)a * b / m;
	ll r = a * b - m * k;
	while (r < 0) r += m;
	while (r >= m) r -= m;
	a = r;
}

inline ll Pow( ll x, ll n ) {
	ll r = m > 1 ? 1 : 0;
	for (; n; n /= 2) {
		if (n & 1)
			Mul(r, x);
		Mul(x, x);
	}
	return r;
}

void Euclid( ll a, ll b, ll &x, ll &y ) { // a * x + b * y = gcd
	if (!b) {
		x = 1, y = 0;
		return;
	}
	ll k = a / b;
	Euclid(b, a % b, x, y);
	swap(x, y), y -= k * x;
}

ll Inv( ll a ) { // x * a + y * m == 1
	ll x, y;
	Euclid(m, a, y, x);
	return x < 0 ? x + m : x;
}

bool bad;
vector<ll> a[2], b[2];

ll solve( ll m ) {
	ll res = 1;
	bad = 0;
	forn(t, 2)
		b[t] = a[t];
	auto use = [&]( ll p, int cnt ) {
		if (cnt < 0)
			bad = 1;
		else 
			Mul(res, Pow(p, cnt));
	};
	forn(i, pn) 
		if (m % p[i] == 0) {
			int cnt = 0, k = 0;
			while (m % p[i] == 0)
				m /= p[i], k++;
			forn(t, 2)
				for (ll &x : b[t])
					while (x % p[i] == 0)
						x /= p[i], cnt += (t ? -1 : 1);
			use(p[i], cnt);
		}

	vector<ll> d = {m}; 
	forn(t, 2)
		for (ll x : b[t]) {
			ll g = __gcd(x, m);
			if (g != m && g != 1) {
				d = {g, m / g};
				goto end;
			}
		}				
	end:
	vector<int> cnt(d.size());
	forn(t, 2)
		for (ll &x : b[t]) {
			forn(i, d.size())
				if (d[i] != 1)
					while (x % d[i] == 0)
						x /= d[i], cnt[i] += (t ? -1 : 1);
			Mul(res, t ? Inv(x) : x);
		}
	forn(i, d.size())
		use(d[i], cnt[i]);
	return res;
}

int main() {
	for (int i = 2; i * i < M; i++)
		if (!p[i])
			for (int j = i * i; j < M; j += i)
				p[j] = 1;
	for (int i = 2; i < M; i++)
		if (!p[i])
			p[pn++] = i;

	forn(t, 2) {
		int n;
		cin >> n;
		a[t].resize(n);
	}
	forn(t, 2)
		for (ll &x : a[t])
			cin >> x;

	int k;
	cin >> k;
	while (k--) {
		cin >> m;
		ll ans = solve(m);
		if (bad)
			cout << "DIVISION BY ZERO\n";
		else
			cout << ans % m << "\n";
	}
}
