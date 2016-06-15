#include <cstdio>
#include <algorithm>

typedef long long ll;

ll gcdEx(ll a, ll b, ll *x, ll *y) {
    if(b==0){
        *x = 1,*y = 0;
        return a;
    }
    else{
        ll r = gcdEx(b, a%b, x, y);
        ll t = *x;
        *x = *y;
        *y = t - a/b * *y;
        return r;
    }
}

long long n, m, a, k;

int main() {
	while (true) {
		scanf("%I64d%I64d%I64d%I64d", &n, &m, &a, &k);
		if (n + m + a + k == 0) break;
		if (m == 0 && k == 0) {
			if (n == a) printf("%I64d\n", a);
			else printf("Impossible\n");
			continue;
		}
		if (a > n) std::swap(a, n), std::swap(m, k);
		ll x, y;
		ll d = gcdEx(m, -k, &x, &y);
		if ((a - n) % d) {
			printf("Impossible\n");
			continue;
		}
		ll t = m / d;
		y = (y % t + t) % t * (a - n) / d;
		printf("%I64d\n", y * k + a);
	}
	return 0;
}