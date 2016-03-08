#include<iostream>
#include<cstring>
#include<vector>
#include<cstdio>
#include<cmath>
#include<algorithm>
#define MAX_N 123
#define MAX_K 6
using namespace std;

typedef long long ll;

ll C[MAX_N][MAX_K];
ll x,y,z;
ll k;
const double eps=1e-8;
double Get(ll aa,ll xx){
	double ret=0;
	for(int i=1;i<=k;i+=2){
		double A=C[xx][2]+xx,B=aa*(xx-aa+1);
		if(fabs(k-i)>eps)
			ret+=C[k][i]*pow(A-B,(double)k-i)*pow(B,(double)i);
		else
			ret+=C[k][i]*pow(B,(double)i);
	}
	return ret;
}

int main(){
	C[0][0]=1;
	for(int i=1;i<MAX_N;i++)
		for(int j=0;j<MAX_K;j++)
			C[i][j]=C[i-1][j]+(j>0?C[i-1][j-1]:0);
	k=1;
	cin>>x>>y>>z>>k;
	if(k==0){
		cout<<x*y*z<<endl;
		return 0;
	}
	double ans=0.0;
	double tot=(double)(C[x][2]+x)*(C[y][2]+y)*(C[z][2]+z);
	for(int a=1;a<=x;a++)
		for(int b=1;b<=y;b++)
			for(int c=1;c<=z;c++)
				ans+=(tot-Get(a,x)*Get(b,y)*Get(c,z))/tot;
	cout<<ans<<endl;
	return 0;
}
