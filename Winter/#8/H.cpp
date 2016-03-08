#include<iostream>
#include<cstring>
#include<vector>
#include<cstdio>
#include<climits>
#define MAX_N 1000
using namespace std;

typedef long long ll;

long long prime[MAX_N],tot;
bool check[MAX_N];

void Euler(){
	memset(check,0,sizeof(check));
	for(int i=2;i<MAX_N;i++){
		if(!check[i])prime[tot++]=i;
		for(int j=0;j<tot;j++){
			if(prime[j]*i>MAX_N)break;
			check[prime[j]*i]=1;
			if(i%prime[j]==0)break;
		}
	}
}

ll haha[MAX_N];
int si=0;
void init(){
	haha[0]=1;
	for(si=1;;si++){
		haha[si]=haha[si-1]*prime[si-1];
		if(haha[si]>INT_MAX)break;
	}
}

long long n;

long long a[MAX_N];

int main(){
	Euler();
	init();
	while(true){
		scanf("%lld",&n);
		ll tmp=n;
		if(n==0)break;
		for(int i=si;i>=0;i--){
			a[i]=n/haha[i];
			n%=haha[i];
		}
		printf("%lld = ",tmp);
		bool flag=false;
		if(a[0]!=0){
			flag=true;
			printf("%lld",a[0]);
		}
		for(int i=1;i<=si;i++){
			if(a[i]!=0){
				if(flag)
					printf(" + ");
				printf("%lld",a[i]);
				flag=true;
				for(int j=0;j<i;j++)
					printf("*%lld",prime[j]);
			}
		}
		printf("\n");
	}
	return 0;
}