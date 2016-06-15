#include <cstdio>
#include <cstring>
#include <algorithm>

#define MAX_N 1003

char str[MAX_N];

void getfail(char *pattern, int *fail) {
    int m = strlen(pattern);
    fail[0]=0;
    fail[1]=0;
    for (int i = 1; i < m; i++) {
        int j = fail[i];
        while (j && pattern[i] != pattern[j]) j = fail[j];
        fail[i+1] = pattern[i] == pattern[j] ? j + 1 : 0;
    }
}

int fail[MAX_N];

int loopTime(int s, int t) {
	int L = t - s + 1;
	if (L % (L - fail[t + 1]) == 0)
		return L / (L - fail[t + 1]);
	else
		return 1;
}

int pre[MAX_N][MAX_N], suf[MAX_N][MAX_N];
long long sum[MAX_N][MAX_N];
int main() {
	scanf("%s", str);
	int len = strlen(str);
	for (int i = 0; i < len; i++) {
		getfail(str + i, fail + i);
		for (int j = i; j < len; j++) 
			pre[j][loopTime(i, j)]++;
	}
	std::reverse(str, str + len);
	for (int i = 0; i < len; i++) {
		getfail(str + i, fail + i);
		for (int j = i; j < len; j++)
			suf[len - j - 1][loopTime(i, j)]++;
	}

	for (int i = 0; i < len; i++)
		for (int j = 0; j < len; j++) {
			if (i > 0)
				sum[i][j] = sum[i - 1][j] + pre[i][j];
			else
				sum[i][j] = pre[i][j];
		}
	long long ans = 0;
	for (int i = 0; i < len - 1; i++)
		for (int j = 0; j <= len; j++)
			ans = ans + sum[i][j] * suf[i + 1][j];
	printf("%lld\n", ans);
	return 0;
}