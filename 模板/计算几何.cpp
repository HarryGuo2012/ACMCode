#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
#include<queue>
#include<cmath>
#include<cstdio>
using namespace std;

const double eps=1e-8;
double inf=1008611;

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

/*------line------*/
struct line{
	point a,b;
	line(){}
	line(point x,point y):a(x),b(y){}
};

line point_make_line(const point a,const point b){
	return line(a,b);
}

double dis_point_segment(const point p,const point s,const point t){
	if(cmp(dot(p-s,t-s))<0)return (p-s).norm();
	if(cmp(dot(p-t,s-t))<0)return (p-t).norm();
	return fabs(det(s-p,t-p))/dist(s,t);
}

bool parallel(line a,line b){
	return !cmp(det(a.a-a.b,b.a-b.b));
}

bool line_make_point(line a,line b,point &res){
	if(parallel(a,b))return false;
	double s1=det(a.a-b.a,b.b-b.a);
	double s2=det(a.b-b.a,b.b-b.a);
	res=(s1*a.b-s2*a.a)/(s1-s2);
	return true;
}
/*------line------*/

/*------polygon------*/
const int maxn=100;
struct polygon{
	int n;
	point a[maxn];
	polygon(){}
	double area(){
		double sum=0;
		a[n]=a[0];
		for(int i=0;i<n;i++)sum+=det(a[i+1],a[i]);
		return sum/2.0;
	}
};
/*------polygon------*/

/*------ConvexHull------*/
struct poly_convex{
	vector<point> P;
	poly_convex(int Size=0){
		P.resize(Size);
	}
};

bool comp_less(const point &a,const point &b){
	return cmp(a.x-b.x)<0||cmp(a.x-b.x)==0&&cmp(a.y-b.y)<0;
}

poly_convex convex_hull(vector<point> a){
	poly_convex res(2*a.size()+5);
	sort(a.begin(),a.end(),comp_less);
	a.erase(unique(a.begin(),a.end()),a.end());
	int m=0;
	for(int i=0;i<a.size();i++){
		while(m>1&&cmp(det(res.P[m-1]-res.P[m-2],a[i]-res.P[m-1]))<=0)--m;
		res.P[m++]=a[i];
	}
	int k=m;
	for(int i=int(a.size())-2;i>=0;i--){
		while(m>k&&cmp(det(res.P[m-1]-res.P[m-2],a[i]-res.P[m-2]))<=0)--m;
		res.P[m++]=a[i];
	}
	res.P.resize(m);
	if(a.size()>1)res.P.resize(m-1);
	return res;
}

bool contain(const poly_convex &a,const point &b){
	int n=a.P.size();
#define next(i) ((i+1)%n)
	int sign=0;
	for(int i=0;i<n;i++){
		int x=cmp(det(a.P[i]-b,a.P[next(i)]-b));
		if(x){
			if(sign){
				if(sign!=x)return false;
			}
			else sign=x;
		}
	}
	return true;
}
/*------ConvexHull------*/

/*------halfPlane-----*/
struct halfPlane{
	double a,b,c;
	halfPlane(point p,point q){
		a=p.y-q.y;
		b=q.x-p.x;
		c=det(p,q);
	}
	halfPlane(double aa,double bb,double cc):a(aa),b(bb),c(cc){}
};

double calc(halfPlane &L,point &a){
	return a.x*L.a+a.y*L.b+L.c;
}

point Inersect(point &a,point &b,halfPlane &L){
	point res;
	double t1=calc(L,a),t2=calc(L,b);
	res.x=(t2*a.x-t1*b.x)/(t2-t1);
	res.y=(t2*a.y-t1*b.y)/(t2-t1);
	return res;
}

poly_convex cut(poly_convex &a,halfPlane &L){
	int n=a.P.size();
	poly_convex res;
	for(int i=0;i<n;i++){
		if(calc(L,a.P[i])<-eps)res.P.push_back(a.P[i]);
		else{
			int j=i-1;
			if(j<0)j=n-1;
			if(calc(L,a.P[j])<-eps)
				res.P.push_back(Inersect(a.P[j],a.P[i],L));
			j=i+1;
			if(j==n)j=0;
			if(calc(L,a.P[j])<-eps)
				res.P.push_back(Inersect(a.P[i],a.P[j],L));
		}
	}
	return res;
}

/*------halfPlane-----*/

int main(){
	return 0;
}
