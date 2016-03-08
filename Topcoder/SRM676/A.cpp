#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
#include<queue>
#define MAX_N 55
using namespace std;

struct node{
	int t,c;
	node(int tt,int cc):t(tt),c(cc){}
	node(){}
};

bool cmp(node a,node b){
	return a.c<b.c;
}

node v[MAX_N];

class FarmvilleDiv2{
	public:
		int minTime(vector <int> tim, vector <int> cost, int budget){
			int n=cost.size();
			for(int i=0;i<n;i++)
				v[i]=node(tim[i],cost[i]);
			sort(v,v+n,cmp);
			int sum=0;
			for(int i=0;i<n;i++){
				int c=v[i].t*v[i].c;
				if(budget>=c){
					budget-=c;
					continue;
				}
				int d=budget/v[i].c;
				sum+=v[i].t-d;
				budget%=v[i].c;
			}
			return sum;
		}
};
