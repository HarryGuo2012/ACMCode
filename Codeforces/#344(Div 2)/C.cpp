#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#define MAX_N 200005
using namespace std;

struct node{
	int t,r,tim;
	node(int tt,int rr,int timm):t(tt),r(rr),tim(timm){}
	node(){}
};

bool cmp(node x,node y){
	if(x.r==y.r)return x.tim<y.tim;
	return x.r<y.r;
}

vector<node> v;
vector<node> vv;
vector<int> ans;

vector<int> tmp;

int n,m;
int a[MAX_N];
int main(){
	cin.sync_with_stdio(false);
	cin>>n>>m;
	for(int i=0;i<n;i++)
		cin>>a[i];
	for(int i=0;i<m;i++){
		int t,r;
		cin>>t>>r;r--;
		v.push_back(node(t,r,i));
	}
	sort(v.begin(),v.end(),cmp);
	int now=-1;
	for(int i=v.size()-1;i>=0;i--){
		if(v[i].tim<=now)continue;
		now=v[i].tim;
		vv.push_back(v[i]);
	}
	for(int i=n-1;i>vv[0].r;i--)
		ans.push_back(a[i]);
	for(int i=0;i<=vv[0].r;i++)
		tmp.push_back(a[i]);
	sort(tmp.begin(),tmp.end());
	int x=0,y=tmp.size()-1;
	for(int i=0;i<vv.size();i++){
		int L;
		if(i!=vv.size()-1)
			L=vv[i].r-vv[i+1].r;
		else
			L=vv[i].r+1;
		for(int j=0;j<L;j++){
			if(vv[i].t==1){
				ans.push_back(tmp[y]);
				y--;
			}
			else{
				ans.push_back(tmp[x]);
				x++;
			}
		}
	}
	for(int i=ans.size()-1;i>=0;i--)
		cout<<ans[i]<<" ";
	cout<<endl;//cin>>n;
	return 0;
}