#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdio>
#define MAX_N 100005
#define INF 3e18
using namespace std;

typedef long long ll;
const long double eps=1e-8;

struct node{
	ll x,y;
	int id;
	node(ll xx,ll yy,int ii):x(xx),y(yy),id(ii){}
	node(){}
	void input(int i){
		scanf("%I64d%I64d",&x,&y);
		id=i;
	}
	node operator-(node a){
		return node(x-a.x,y-a.y,0);
	}
}a[MAX_N];

bool cmp(node u,node v){
	if(u.x==v.x)return u.y<v.y;
	return u.x<v.x;
}

long double det(node u,node v){
	return u.x*v.y-u.y*v.x;
}

int n;

long double getDis(node i,node j){
	long double xx=i.x-j.x;
	long double yy=i.y-j.y;
	return sqrt(xx*xx+yy*yy);
}

long double S(int i,int j,int k){
	return det(a[i]-a[j],a[j]-a[k]);
}

node f;

bool cmp2(node i,node j){
	return getDis(f,i)<getDis(f,j);
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		a[i].input(i);
	sort(a+1,a+1+n,cmp);
	sort(a+1,a+1+n,cmp2);
	int p;
	long double ar=INF;//cout<<ar<<endl;
	for(int i=3;i<=n;i++){
		long double tmp=S(1,2,i);
		if(fabs(tmp)>eps){p=i;break;}
	}
	cout<<a[1].id<<" "<<a[2].id<<" "<<a[p].id<<endl;
	//char cc;cin>>cc;
	return 0;
}