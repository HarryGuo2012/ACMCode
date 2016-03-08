#include <iostream>
#include <cmath>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;

struct Line{
	double a,b;
	void input(){
		scanf("%lf%lf",&a,&b);
	}
};

vector<Line> v;
stack<Line> s;
#define st s

bool cmp(Line x,Line y){
	if(x.a==y.a)return x.b<y.b;
	return x.a<y.a;
}

struct Point{
	double x,y;
	Point(double xx,double yy):x(xx),y(yy){}
	Point(){}
	friend Point operator-(Point a,Point b){
		return Point(a.x-b.x,a.y-b.y);
	}
};

double det(Point a,Point b){
	return a.x*b.y-a.y*b.x;
}

Point cro(Line l1,Line l2){
	double x=(l2.b-l1.b)/(l1.a-l2.a);
	double y=l1.a*x+l1.b;
	return Point(x,y);
}

int T,n;

const double eps=1e-8;

bool check(int i){
	if(s.size()==0)return true;
	Line l2=st.top();st.pop();
	Line l3=v[i];
	if(l3.a==l2.a){
		st.push(l2);
		return false;
	}
	if(s.size()==0){
		st.push(l2);
		return true;
	}
	Line l1=st.top();st.pop();
	Point p2=cro(l1,l2),p1;
	//cout<<p2.x<<" "<<p2.y<<endl;
	p1.y=l1.a*(p2.x-10)+l1.b;
	p1.x=p2.x-10;
	Point p3=cro(l2,l3);
	//cout<<p3.x<<" "<<p3.y<<endl;
	Point v1=p2-p1,v2=p3-p2;
	//cout<<"**"<<endl;
	st.push(l1);st.push(l2);
	return det(v1,v2)>0;
}

int main(){
	scanf("%d",&T);
	while(T--){
		while(s.size())s.pop();
		v.clear();
		scanf("%d",&n);
		for(int i=0;i<n;i++){
			Line l;
			l.input();
			v.push_back(l);
		}
		sort(v.begin(),v.end(),cmp);
		for(int i=0;i<v.size();i++){
			while(!check(i))
				st.pop();
			st.push(v[i]);
		}
		printf("%d\n",st.size());
	}
	return 0;
}