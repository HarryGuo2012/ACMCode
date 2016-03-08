#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
#include<algorithm>
#include<map>
#define MAX_N 50000007
using namespace std;

map<int,int> ma;

void div(int x){
	while(x>1){
		for(int i=2;i<=x;i++)
			if(x%i==0){
				x/=i;
				ma[i]++;
				break;
			}
	}
}

typedef long long ll;

//返回d=gcd(a,b);和对应于等式ax+by=d中的x,y
long long extend_gcd(long long a,long long b,long long &x,long long &y)
{
    if(a==0&&b==0) return -1;//无最大公约数
    if(b==0){x=1;y=0;return a;}
    long long d=extend_gcd(b,a%b,y,x);
    y-=a/b*x;
    return d;
}
//*********求逆元素*******************
//ax = 1(mod n)
long long mod_reverse(long long a,long long n)
{
    long long x,y;
    long long d=extend_gcd(a,n,x,y);
    if(d==1) return (x%n+n)%n;
    else return -1;
}

ll mod=9901;

ll Pow(ll a,ll b,ll m){
	ll res=1;
	while(b){
		if(b&1)res*=a;
		b>>=1;
		a=a*a%m;
		res%=m;
	}
	return res;
}

int main(){
	ll n,m;
	while(cin>>n>>m){
		if(m==0){
			cout<<1<<endl;
			continue;
		}
	
		ma.clear();
		div(n);
		ll res=1;
		for(map<int,int>::iterator it=ma.begin();it!=ma.end();it++){
			ll p=it->first,a=it->second;
			if((p-1)%mod==0){
				ll tmp=Pow(p,a*m+1,mod*(p-1))+mod*(p-1)-1;
				res=res*tmp/(p-1)%mod;
			}
			else{
				ll tmp=Pow(p,a*m+1,mod)+mod-1;
				res=res*tmp*mod_reverse(p-1,mod)%mod;
			}
		}
		cout<<res<<endl;
	}
	return 0;
}
