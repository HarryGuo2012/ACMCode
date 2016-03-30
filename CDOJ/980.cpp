#include <cstdio>
#include <algorithm>

int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		int a, b;
		scanf("%d%d", &a, &b);
		printf("%d %d\n", std::__gcd(a, b), a * b / std::__gcd(a, b));
	}
	return 0;
}