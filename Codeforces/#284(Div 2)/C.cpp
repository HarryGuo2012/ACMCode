#include<iostream>
#include<cstring>
#include<cmath>
#include<vector>
#include<cstdio>
using namespace std;

const double inf=1e8;
const double eps=1e-8;

int cmp(double x){
	if(fabs(x)<eps)return 0;
	if(x>0)return 1;
	return -1;
}

double sqr(double x){
	return x*x;
}
/*------point------*/
struct point{
	double x,y;
	point(){}
	point(double a,double b):x(a),y(b){}
	void input(){
		scanf("%lf%lf",&x,&y);
	}
	friend point operator+(const point &a,const point &b){
		return point(a.x+b.x,a.y+b.y);
	}
	friend point operator-(const point &a,const point &b){
		return point(a.x-b.x,a.y-b.y);
	}
	friend bool operator==(const point &a,const point &b){
		return cmp(a.x-b.x)==0&&cmp(a.y-b.y)==0;
	}
	friend point operator*(const point &a,const double &b){
		return point(a.x*b,a.y*b);
	}
	friend point operator*(const double &a,const point &b){
		return b*a;
	}
	friend point operator/(const point &a,const double &b){
		return a*(1/b);
	}
	double norm(){
		return sqrt(sqr(x)+sqr(y));
	}
};

double det(const point &a,const point &b){
	return a.x*b.y-a.y*b.x;
}

double dot(const point &a,const point &b){
	return a.x*b.x+a.y*b.y;
}

double dist(const point &a,const point &b){
	return a.x*b.y-a.y*b.x;
}

/*------point------*/

point h,s;

typedef point Vector;

int main(){
	h.input();
	s.input();
	int n;
	scanf("%d",&n);
	int cnt=0;
	while(n--){
		double a,b,c;
		scanf("%lf%lf%lf",&a,&b,&c);
		a+=eps,b+=eps,c+=eps;
		point A(inf,-(a*inf+c)/b);
		point B(-inf,-(-a*inf+c)/b);
		Vector v=B-A,u0=h-A,u1=s-A;
		if(cmp(det(v,u0))!=cmp(det(v,u1)))
			cnt++;
	}
	cout<<cnt<<endl;
	return 0;
}
