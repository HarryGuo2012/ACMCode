#include<iostream>
#include<cmath>
#include<vector>
#include<algorithm>
#include<cstring>
#include<cstdio>
#define MAX_N 100005
using namespace std;

double sqr(double x){
	return x*x;
}

struct Point{
	double x,y;
	Point(double xx,double yy):x(xx),y(yy){}
	Point(){x=0.0;y=0.0;}
	void input(){
		scanf("%lf%lf",&x,&y);
	}	
	void output(){
		printf("%.5f %.5f\n",x,y);
	}
	Point operator-(Point a){
		return Point(x-a.x,y-a.y);
	}
	Point operator+(Point a){
		return Point(x+a.x,y+a.y);
	}
	double norm(){
		return sqrt(sqr(x)+sqr(y));
	}
	Point operator*(double a){
		return Point(a*x,a*y);
	}
};

typedef Point Vector;

double dot(Vector a,Vector b){
	return a.x*b.x+a.y*b.y;
}

double getAngle(Vector a,Vector b){
	return dot(a,b)/(a.norm()*b.norm());
}

Point S,F;
Vector SF;

Vector v,a[MAX_N];
Vector w[MAX_N],sw;
Vector B;
int tim[MAX_N];
int n,k;
double vmax;
const double eps=1e-5;
int main(){
	freopen("joy.in","r",stdin);
	freopen("joy.out","w",stdout);
	S.input();F.input();
	SF=F-S;
	scanf("%d%d%lf",&n,&k,&vmax);
	for(int i=0;i<n;i++){
		scanf("%d",&tim[i]);
		w[i].input();
	}
	for(int i=0;i<n;i++){
		int tmp;
		if(i==n-1)
			tmp=k;
		else 
			tmp=tim[i+1];
		sw=sw+w[i]*(tmp-tim[i]);
	}
	if(S.x==F.x&&S.y==F.y){
		printf("Yes\n");
		for(int i=0;i<k;i++)
			F.output();
		return 0;
	}
	B=SF-sw;
	if(vmax*k<B.norm()-eps){
		printf("No\n");
		return 0;
	}
	printf("Yes\n");
	if(fabs(B.norm())<eps){
		for(int i=0;i<k;i++)
			F.output();
		return 0;
	}
	v=B*(1.0/k);
	for(int i=0;i<n;i++){
		int tmp;
		if(i==n-1)
			tmp=k;
		else 
			tmp=tim[i+1];
		for(int j=tim[i];j<tmp;j++)
			a[j]=v+w[i];
	}
	Point now=S;
	for(int i=0;i<k;i++){
		now=now+a[i];
		now.output();
	}
	return 0;
}
