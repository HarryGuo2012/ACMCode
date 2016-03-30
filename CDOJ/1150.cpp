#include <cstdio>
#include <set>
#include <algorithm>
#include <vector>
#include <cmath>

#define MAX_N 1024

const double pi = acos(-1);
const double eps = 1e-6;

struct Point{
	double x, y;
	Point(double xx, double yy) : x(xx), y(yy){}
	Point(){}

	Point operator + (Point);
	Point operator - (Point);
	double norm()
	void input();
};

typedef Point Vector;

Point Point::operator + (Point a){
	return Point(x + a.x, y + a.y);
}

Point Point::operator - (Point a){
	return Point(x - a.x, y - a.y);
}

bool pointCmp(const Point &a, const Point &b){
	if(a.x == b.x)
		return a.y < b.y;
	return a.x < b.x;
}

void Point::input(){
	scanf("%lf%lf", &x, &y);
}

double Point::norm(){
	return sqrt(x * x + y * y);
}

double det(Vector a, Vector b){
	return a.x * b.y - a.y * b.x;
}

double dot(Vector a, Vector b){
	return a.x * b.x + a.y * b.y;
}

double getAngle(Vector a, Vector b){
	return dot(a, b) / (a.norm() * b.norm());
}

double angleOfX(Vector a){
	return getAngle(a, Vector(1, 0));
}

std::vector<double> allAngle;

int solve(int x){
	for(int i = 0; i < po.size(); i++){
		if(i != x)
			allAngle.push_back(angleOfX(po[i] - po[x]));
	}
	std::sort(allAngle.begin(), allAngle.end());
	for(int i = 0; i < po.size(); i++){
		if(i == x) continue;
	}
}

int T, N;

std::vector<Point> po;
std::set<Point, pointCmp> se;

int main(){
	scanf("%d", &T);
	while(T--){
		int ans = 0;
		scanf("%d", &N);
		for(int i = 0; i < N; i++){
			Point p;
			p.input();
			se.insert(p);
		}
		for(auto p : se)
			po.push_back(p);
		for(int i = 0; i < po.size(); i++)
			ans += solve(i);
	}
	return 0;
}