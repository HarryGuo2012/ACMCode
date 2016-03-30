#include <cstdio>

#define MAX_N 33

long long v[MAX_N];

int main(){
	int n;
	scanf("%d", &n);
	v[0] = 1;
	for(int i = 1; i < n; i++)
		v[i] = (v[i - 1] + 1) * 3;
	for(int i = n - 1; i >= 0; i--)
		printf("%lld ", v[i]);
	printf("\n");
	return 0;
}