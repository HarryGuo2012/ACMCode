#include <cstdio>
#include <cstring>

#define MAX_N 1000006

int prime[MAX_N];
bool check[MAX_N];
int tot = 0;

void Euler(){
	memset(check,0,sizeof(check));
	for(int i=2;i<MAX_N;i++){
		if(!check[i])prime[tot++]=i;
		for(int j=0;j<tot;j++){
			if(prime[j]*i>=MAX_N)break;
			check[prime[j]*i]=1;
			if(i%prime[j]==0)break;
		}
	}
}

int main() {
	Euler();
	long long X = 600851475143;
	int i = 0;
	while (X > 1) {
		while (X > 1 && X % prime[i] == 0) X /= prime[i];
		i++;
		if (i >= tot) break;
	}
	if (X == 1) printf("%d\n", prime[i - 1]);
	else printf("%lld\n", X);
	return 0;
}