#include<bits/stdc++.h>
using namespace std;
#define LL long long
const int maxn=1000006;
const double pi=acos(-1.0);
struct Complex {
    double x,y;
    Complex(double xx,double yy):x(xx),y(yy) {}
    Complex() {}
    Complex operator + (Complex a) {
        return Complex(a.x+x,a.y+y);
    }
    Complex operator - (Complex a) {
        return Complex(x-a.x,y-a.y);
    }
    Complex operator * (Complex a) {
        return Complex(x*a.x-y*a.y,x*a.y+y*a.x);
    }

};
void build(Complex _P[],Complex P[],int n,int m,int curr,int &cnt) {
    if (m==n) {
        _P[curr]=P[cnt++];
    } else {
        build(_P,P,n,m*2,curr,cnt);
        build(_P,P,n,m*2,curr+m,cnt);
    }
}
void FFT(Complex P[],int n,int oper) {
    static Complex _P[maxn];
    int cnt=0;
    build(_P,P,n,1,0,cnt);
    copy(_P,_P+n,P);
    for (int d=0; (1<<d)<n; d++) {
        int m=1<<d;
        int m2=m*2;
        double p0=pi/m*oper;
        Complex unit_p0=Complex(cos(p0),sin(p0));
        for (int i=0; i<n; i+=m2) {
            Complex unit=Complex(1,0);
            for (int j=0; j<m; j++) {
                Complex &P1=P[i+j+m],&P2=P[i+j];
                Complex t=unit * P1;
                P1=P2-t;
                P2=P2+t;
                unit=unit*unit_p0;
            }

        }
    }
}
Complex P[15][maxn],Q[maxn];
int n,m;long long ha[maxn];
int main() {
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++){
		int t;scanf("%d",&t);
		P[0][t]=Complex(1,0);
	}
	int k=1;
	while(k<=n)k<<=1;k<<=1;
	FFT(P[0],,1);
	for(int i=1;i<11;i++)
		for(int j=0;j<=k;j++)
			P[i][j]=P[i-1][j]*P[i-1][j];
	for(int i=0;i<11;i++){
		if((1<<i)&m)for(int j=0;j<=k;j++)
			Q[j]=Q[j]*P[i][j];
	}
	FFT(Q,k,-1);
	for(int j=0;j<=k;j++)ha[j]=(LL)(Q[j].x/k+0.5);
	for(int i=0;i<=k;i++)if(ha[i])printf("%d ",i+1);
	printf("\n");cin>>n;
    return 0;
}
