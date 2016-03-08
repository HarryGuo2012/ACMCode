#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <string>
#include <cmath>
#include <queue>
#include <vector>
#include <map>
#include <set>
#define MAX_N 100005
using namespace std;

struct treenode{
	int L,R;double sum;int num;
  	void updata(double v){
    sum += v;
  }
};

treenode tree[500000];

void push_up(int o){
	tree[o].sum = max(tree[2*o].sum , tree[2*o+1].sum);
	if(tree[2*o].sum>tree[2*o+1].sum)
        tree[o].num=tree[2*o].num;
    else
        tree[o].num=tree[2*o+1].num;
}

void build_tree(int L , int R , int o){
	tree[o].L = L , tree[o].R = R,tree[o].sum = 0;
	tree[o].num = L;
	if (R > L){
		int mid = (L+R) >> 1;
		build_tree(L,mid,o*2);
		build_tree(mid+1,R,o*2+1);
	}
}

void updata(int l,int r,double v,int o){
	int L = tree[o].L , R = tree[o].R;
	if (l <= L && R <= r) 
		tree[o].updata(v);
	else{
		int mid = (L+R)>>1;
		if (l <= mid) updata(l,r,v,o*2);
		if (r >  mid) updata(l,r,v,o*2+1);
		push_up(o);
	}
}
void updata2(int l,int r,double v,int o){
	int L = tree[o].L , R = tree[o].R;
	if (l <= L && R <= r)
        tree[o].sum=max(tree[o].sum,v);
	else{
		int mid = (L+R)>>1;
		if (l <= mid) updata2(l,r,v,o*2);
		if (r >  mid) updata2(l,r,v,o*2+1);
		push_up(o);
	}
}
double query(int l,int r,int o){
    if(r<l)return 0;
	int L = tree[o].L , R = tree[o].R;
	if (l <= L && R <= r) return tree[o].sum;
	else{
		int mid = (L+R)>>1;
		double res = 0;
		if (l <= mid) res = max(query(l,r,2*o),res);
		if (r > mid) res = max(query(l,r,2*o+1),res);
		push_up(o);
		return res;
	}
}


double h[MAX_N],r[MAX_N],v[MAX_N];
const double pi = acos(-1.0);
vector<double> vd;
map<double,int> ma;
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%lf%lf",&r[i],&h[i]),v[i]=pi*r[i]*r[i]*h[i];
        vd.push_back(v[i]);
    }
    sort(vd.begin(),vd.end());
    vd.erase(unique(vd.begin(),vd.end()),vd.end());
    for(int i=0;i<vd.size();i++)
        ma[vd[i]]=i+1;
    build_tree(1,n,1);
    for(int i=1;i<=n;i++){
        double p = v[i]+query(1,ma[v[i]]-1,1);
        updata2(ma[v[i]],ma[v[i]],p,1);
    }
    printf("%.9f\n",tree[1].sum);
    return 0;
}
