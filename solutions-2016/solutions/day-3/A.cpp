#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int L = 100005;

int n, m, g;

char s[L], t[L];

int sc[L][3], tc[L][3];

int num(char ch) {
	if (ch == 'R') {
		return 0;
	} else if (ch == 'P') {
		return 1;
	} else {
		return 2;
	}
}

int main() {
	scanf("%s%s", s, t);
	n = strlen(s), m = strlen(t);
	g = __gcd(n, m);
	for (int i = 0; i < n; ++i) {
		sc[i % g][num(s[i])]++;
	}
	for (int i = 0; i < m; ++i) {
		tc[i % g][num(t[i])]++;
	}
	long long ans = 0;
	for (int i = 0; i < g; ++i) {
		for (int j = 0; j < 3; ++j) {
			ans += (long long)sc[i][j] * tc[i][(j + 2) % 3];
			ans -= (long long)sc[i][j] * tc[i][(j + 1) % 3];
		}
	}
	if (ans > 0) {
		puts("TankEngineer");
	} else if (ans < 0) {
		puts("AngryBacon");
	} else {
		puts("Rowdark");
	}
	return 0;
}