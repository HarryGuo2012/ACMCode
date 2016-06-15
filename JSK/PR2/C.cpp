#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const long long P = 1LL << 30;

vector< int > Table[4002];

int Mobius[4002] , visited[4002];
long long dp[4002][4002];

void init() {
	for (int i = 1; i <= 4000; i++) 
		Mobius[i] = 1;
	for (int i = 2; i <= 4000; i++)
	 if (!visited[i]) { 
	 	for (int j = i; j <= 4000; j += i) {
	 		if((j / i) % i == 0) 
	 			Mobius[j] = 0;
	 		else Mobius[j] = -Mobius[j];
	 		visited[j] = 1;
	 	}
	}
	for (int i = 1; i <= 4000; i++)
		for(int j = i; j <= 4000; j += i)
			Table[j].push_back(i);
}

long long solve(int n, int m, int a, int b, int bs) {
	long long ans = 0;
	for (int i = 1; i <= n; i++)
		for(int j = 0; j < Table[i].size(); j++) {
			int d = Table[i][j] , t = m / d;
			ans = ans + Mobius[d] * 
			(t * (a * b + a - bs * b * i - bs * i + b + 1) + 
				d * ( bs * bs * i - bs * a -  bs )*
				( (t + 1) * t / 2 ) ) ;
			ans = (ans % P + P) % P;
		}
	return ans;
}

int main(){
	init();
	int T;
	scanf("%d", &T);
	while(T--) {
		int n, m;
		scanf("%d%d", &n, &m);
		if (n > m) swap(n, m);
		if(dp[n][m]) 
			printf("%lld\n" , dp[n][m]);
		else {
			long long ans = (((solve( n - 1 , m - 1 , n - 1 , m - 1 , 1 )
			 - solve((n - 1)/2 , (m - 1)/2 , n - 1 , m - 1 , 2 ) + P ) % P * 2) + n + m ) % P;
			printf("%lld\n" , ans);
			dp[n][m] = ans;
		}
	}
	return 0;
}
