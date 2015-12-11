#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
#include<cmath>
#include<cstdlib>
#define MAX_N 100005
using namespace std;

const double eps=1e-8;

int cmp(double x){
	if(fabs(x)<eps)return 0;
	if(x>0)return 1;
	return -1;
}

double sqr(double x){
	return x*x;
}

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

struct poly_convex{
	vector<point> P;
	poly_convex(int Size=0){
		P.resize(Size);
	}
};

bool comp_less(const point &a,const point &b){
	return cmp(a.x-b.x)<0||cmp(a.x-b.x)==0&&cmp(a.y-b.y)<0;
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
/*
int contain(const poly_convex &a,const point &b){
	int n=a.P.size();
	point g=(a.P[0]+a.P[n/3]+a.P[2*n/3])/3.0;
	int l=0,r=n;
	while(l+1<r){
		int mid=(l+r)>>1;
		if(cmp(det(a.P[1]-g,a.P[mid]-g))>0){
			if(cmp(det(a.P[1]-g,b-g))>=0&&cmp(det(a.P[mid]-g,b-g))<0)r=mid;
			else l=mid;
		}
		else{
			if(cmp(det(a.P[1]-g,b-g))<0&&cmp(det(a.P[mid]-g,b-g))>=0)l=mid;
			else r=mid;
		}
	}
	r%=n;
	int z=cmp(det(a.P[r]-b,a.P[l]-b))-1;
	if(z==-2)return 1;

	return z;
}
*/

int n;
point p;
vector<point> vp;
poly_convex con;

double xmax=-1,ymax=-1;

int main(){
	scanf("%d",&n);
	p.input();
	for(int i=0;i<n;i++){
		point t;
		t.input();
		xmax=max(xmax,t.x);
		ymax=max(ymax,t.y);
		vp.push_back(t);
	}
	vp.push_back(point(0,0));
	vp.push_back(point(0,ymax));
	vp.push_back(point(xmax,0));
	con=convex_hull(vp);
	double l=0,r=1e7;
	for(int i=0;i<10000;i++){
		double mid=(l+r)/2;
		point tmp(p.x/mid,p.y/mid);
		if(contain(con,tmp))r=mid;
		else l=mid;
	}
	printf("%.8f\n",l);
	return 0;
}
