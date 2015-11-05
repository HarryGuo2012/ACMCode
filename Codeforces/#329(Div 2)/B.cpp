#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#define MAX_N 100005
using namespace std;

int n;

double L,R;

double eps=1e-8;

struct node{
	double u,v;
}a[MAX_N];

bool cmp(node aa,node bb){
	return aa.u<bb.u;
}

int main(){
	cin.sync_with_stdio(false);
	cin>>n;
	cin>>L>>R;
	L+=eps;
	R-=eps;
	for(int i=0;i<n;i++){
		double k,b;
		cin>>k>>b;
		a[i].u=k*L+b;
		a[i].v=k*R+b;
	}
	sort(a,a+n,cmp);
	for(int i=0;i<n-1;i++)
		if(a[i].v>a[i+1].v){
			cout<<"YES"<<endl;
			return 0;
		}
	cout<<"NO"<<endl;
	return 0;
}
