#include<iostream>
#include<bitset>
#include<cstring>
#include<vector>
#include<queue>
#include<cstdio>
#include<algorithm>
#include<cmath>
#define MAX_N 666
using namespace std;

bitset<MAX_N> b[MAX_N];

struct Point{
	int x,y;
	Point(int xx,int yy):x(xx),y(yy){}
	Point(){}
	void input(){
		scanf("%d%d",&x,&y);
	}
};

bool between(double a, double X0, double X1)
{
	double temp1= a-X0;
	double temp2= a-X1;
	if ( ( temp1<1e-8 && temp2>-1e-8 ) || ( temp2<1e-6 && temp1>-1e-8 ) )
	{
		return true;
	}
	else
	{
		return false;
	}
}


// 判断两条直线段是否有交点，有则计算交点的坐标
// p1,p2是直线一的端点坐标
// p3,p4是直线二的端点坐标
bool detectIntersect(Point p1, Point p2, Point p3, Point p4)
{
	double line_x,line_y; //交点
	if ( (fabs(p1.x-p2.x)<1e-6) && (fabs(p3.x-p4.x)<1e-6) )
	{
		return false;
	}
	else if ( (fabs(p1.x-p2.x)<1e-6) ) //如果直线段p1p2垂直与y轴
	{
		if (between(p1.x,p3.x,p4.x))
		{
			double k = (p4.y-p3.y)/(p4.x-p3.x);
			line_x = p1.x;
			line_y = k*(line_x-p3.x)+p3.y;

			if (between(line_y,p1.y,p2.y))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else 
		{
			return false;
		}
	}
	else if ( (fabs(p3.x-p4.x)<1e-6) ) //如果直线段p3p4垂直与y轴
	{
		if (between(p3.x,p1.x,p2.x))
		{
			double k = (p2.y-p1.y)/(p2.x-p1.x);
			line_x = p3.x;
			line_y = k*(line_x-p2.x)+p2.y;

			if (between(line_y,p3.y,p4.y))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else 
		{
			return false;
		}
	}
	else
	{
		double k1 = (p2.y-p1.y)/(p2.x-p1.x); 
		double k2 = (p4.y-p3.y)/(p4.x-p3.x);

		if (fabs(k1-k2)<1e-6)
		{
			return false;
		}
		else 
		{
			line_x = ((p3.y - p1.y) - (k2*p3.x - k1*p1.x)) / (k1-k2);
			line_y = k1*(line_x-p1.x)+p1.y;
		}

		if (between(line_x,p1.x,p2.x)&&between(line_x,p3.x,p4.x))
		{
			return true;
		}
		else 
		{
			return false;
		}
	}
}

struct Seg{
	Point s,t;
};

vector<Seg> A,B;

int n;

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		Seg seg;
		seg.s.input();seg.t.input();
		if(seg.s.x==seg.t.x)
			A.push_back(seg);
		else
			B.push_back(seg);
	}
	for(int i=0;i<A.size();i++)
		for(int j=0;j<B.size();j++)
			if(detectIntersect(A[i].s,A[i].t,B[j].s,B[j].t))
				b[j][i]=1;
	long long ans=0;
	for(int i=0;i<B.size();i++)
		for(int j=0;j<B.size();j++){
			if(i==j)continue;
			bitset<MAX_N> tmp=b[i]&b[j];
			int cnt=tmp.count();
			ans+=(long long)cnt*(cnt-1);
		}
	cout<<ans/4<<endl;
	return 0;
}
