#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>
#include <vector>
#include <cmath>
#include <cstdio>
#define MAX_N 100005
using namespace std;

int n,k;
double h;
const double eps=1e-8;

struct node{
	int m;
	double v;
	int id;
}A[MAX_N];

bool cmp(node a,node b){
	if(a.m==b.m)return a.v<b.v;
	return a.m<b.m;
}

vector<int> G;
vector<int> GG;

bool check(double t){
	G.clear();
	int j=1;
	for(int i=0;i<n;i++)
		if(A[i].v*t>j*h||fabs(A[i].v*t-j*h)<eps){
			G.push_back(A[i].id);
			j++;
		}
	return j>k;
}

int main(){
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	scanf("%d%d%lf",&n,&k,&h);
	for(int i=0;i<n;i++)
		scanf("%d",&A[i].m);
	for(int i=0;i<n;i++)
		scanf("%lf",&A[i].v);
	for(int i=0;i<n;i++)
		A[i].id=i+1;
	sort(A,A+n,cmp);
	double L=0,R=1000000000;
	for(int t=0;t<1000;t++){
		double mid=(L+R)/2;
		if(check(mid)){
			R=mid,GG=G;
			//cout<<GG.size()<<endl;
		}
		else L=mid;
	}
	printf("%d",GG[0]);
	for(int i=1;i<k;i++)
		printf(" %d",GG[i]);
	printf("\n");
	return 0;
}