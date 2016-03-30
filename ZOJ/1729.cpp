#include <cstdio>
#include <vector>

#define MAX_N 3000006

typedef long long ll;

int prime[MAX_N], tot = 0;
bool check[MAX_N];

void Euler(){
	memset(check, 0, sizeof(check));
	for(int i = 2; i < MAX_N; i++){
		if(!check[i]) prime[tot++] = i;
		for(int j = 0; j < tot; j++){
			if(prime[j] * i >= MAX_N) break;
			check[prime[j] * i] = 1;
			if(i % prime[j] == 0) break;
		}
	}
}

std::vector<ll> prFac;//prime factor of n
std::vector<ll> fac;//all factor of n

void getPrFac(ll x){
	prFac.clear();
	for(auto p : prFac){
		if(x )
	}
}

int main(){
	return 0;
}