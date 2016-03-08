#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<cmath>
#define MAX_N 2234
using namespace std;

typedef long long ll;

ll CL[MAX_N];
ll C[MAX_N][MAX_N];
ll A[MAX_N];
ll T[MAX_N];
const ll mod=1000000007;
int main(){
	T[0]=1;
	for(int i=1;i<MAX_N;i++)
		T[i]=(T[i-1]*2)%mod;
	A[0]=1;
	for(int i=1;i<MAX_N;i++)
		A[i]=(A[i-1]*i)%mod;
	C[0][0]=1;
	for(int i=1;i<MAX_N;i++)
		for(int j=0;j<=i;j++){
			if(j==0)
				C[i][j]=1;
			else
				C[i][j]=C[i-1][j]+C[i-1][j-1];
			C[i][j]%=mod;
		}
	for(int i=1;i<MAX_N/2;i++)
		CL[i]=(C[2*i][i]-C[2*i][i+1]+mod)%mod;
	ll n;
	while(true){
		scanf("%I64u",&n);
		if(n==0)break;
		n++;
		printf("%I64u\n",A[n]*T[n-2]%mod*CL[n-1]%mod);
	}
	return 0;
}
