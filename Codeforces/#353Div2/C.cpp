#include <cstdio>
#include <map>

#define MAX_N 100005

long long A[MAX_N], S[MAX_N];
int n;

std::map<long long, int> ma, ma2;

int main() {
	scanf("%d", &n);
	int ans = n;
	for (int i = 1; i <= n; i++) {
		scanf("%I64d", &A[i]);
		S[i] = S[i - 1] + A[i];
		if (S[i] == 0) ans--;
		ma[S[i]]++;
	}
	ma[S[1]]--;
	ma2[S[1]]++;
	for (int i = 2; i <= n; i++) {
		int cnt = 0;
		cnt += ma[S[i - 1]];
		cnt += ma2[-S[n] + S[i - 1]];
		ans = std::min(ans, n - cnt);
		ma[S[i]]--;
		ma2[S[i]]++;
	}
	printf("%d\n", ans);
	return 0;
}