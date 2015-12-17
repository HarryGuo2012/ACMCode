#include<stdio.h>
#include<math.h>
#define maxn 3000000
long long gcd(long long a,long long b){
    return b?gcd(b,a%b):a;
}
 
inline long long lcm(long long a,long long b){
    return a/gcd(a,b)*b;
}
 
long long eular(long long n)    ////求1..n-1中与n互质的数的个数
{
    long long ret=1,i;
    for (i=2;i*i<=n;i++)
        if (n%i==0){
            n/=i,ret*=i-1;
            while (n%i==0)
                n/=i,ret*=i;
        }
    if (n>1)
        ret*=n-1;
    return ret;
}
int main(){
	long long n,x;
	while(scanf("%I64d%I64d",&n,&x)==2){
		printf("%I64d\n",eular(n+x+1));
	}
	return 0;
}
