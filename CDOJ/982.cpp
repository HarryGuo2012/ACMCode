#include <cstdio>
#include <vector>

#define MAX_N 100005

int T;
long long n;

std::vector<long long> v;

long long prime[MAX_N], tot = 0;
bool check[MAX_N];

void Euler(){
	for(int i = 2; i < MAX_N; i++){
		if(check[i] == 0) prime[tot++] = i;
		for(int j = 0; j < tot; j++){
			if(prime[j] * i >= MAX_N) break;
			check[prime[j] * i] = 1;
			if(i % prime[j]) break;
		}
	}
}

int main(){
	Euler();
	scanf("%d", &T);
	while(T--){
		v.clear();
		scanf("%lld", &n);
		int i = 0;
		printf("%lld=", n);
		while(n > 1){
			int u = prime[i];
			if(u * u > n + 5)
				break;
			while(n % u == 0){
				v.push_back(u);
				n /= u;
			}
			i++;
		}
		if(n != 1)
			v.push_back(n);
		printf("%lld", v[0]);
		for(int i = 1; i < v.size(); i++)
			printf("*%lld", v[i]);
		printf("\n");
	}
	return 0;
}