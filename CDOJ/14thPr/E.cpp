#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
const int maxn = 100100;
int n;
char s[maxn];
int cnt[maxn][30], c[maxn];
long long r[30];

int main() {
	scanf("%d",&n);
	for(int i = 0; i < n; i++) {
		scanf("%s",s);
		for(int j = 0; s[j]; j++) cnt[i][s[j]-'a']++;
	}
	for(int i = 0; i < n; i++) scanf("%d",&c[i]);
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < 26; j++) r[j] += (long long)c[i] * cnt[i][j];
	}
	long long res = 0;
	for(int j = 0; j < 26; j++) res = max(res, r[j]);
	cout << res << endl;
	return 0;
}