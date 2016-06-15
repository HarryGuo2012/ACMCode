#include <cstdio>
#include <algorithm>

const int mod = 1 << 30;

int T , N , M;

int main() {
	scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &N, &M);
		N--, M--;
		long long ans = 0;
		for (int i = 1 ; i <= N; i++)
			for (int j = 1; j <= M; j++) {
				int tmp = (N - i + 1) * (M - j + 1);
				int d = std::__gcd( i , j );
				if (d == 1) ans += tmp;
				else if (d == 2) ans -= tmp;
				ans = ans % mod;
				ans = (ans + mod) % mod;
			}
		printf("%lld\n" , (ans * 2 + N + M + 2) % mod);

	}
	return 0;
}
