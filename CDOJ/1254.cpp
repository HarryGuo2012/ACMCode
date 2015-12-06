#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

bool flag=false;
double eps=1e-10;
void dfs(vector<double> v){
	if(flag)return;
	//if(v.size()==1)cout<<v[0]<<endl;
	if(v.size()==1&&abs(v[0]-24)<eps){
		flag=true;
		return;
	}
	for(int i=0;i<v.size();i++)
		for(int j=0;j<v.size();j++){
			if(i==j)continue;
			vector<double> t;
			for(int k=0;k<v.size();k++){
				if(k==i||k==j)continue;
				t.push_back(v[k]);
			}
			vector<double> a=t;
			a.push_back(v[i]+v[j]);
			dfs(a);
			a=t;
			a.push_back(v[i]-v[j]);
			dfs(a);
			a=t;
			a.push_back(v[j]-v[i]);
			dfs(a);
			a=t;
			a.push_back(v[i]*v[j]);
			dfs(a);
			a=t;
			if(abs(v[j])>eps){
				a.push_back(v[i]/v[j]);
				dfs(a);
				a=t;
			}
			if(abs(v[i])>eps){
				a.push_back(v[j]/v[i]);
				dfs(a);
				a=t;
			}
		}
}

int T;
vector<double> v;

int main(){
	scanf("%d",&T);
	while(T--){
		v.clear();
		for(int i=0;i<4;i++){
			int a;
			scanf("%d",&a);
			v.push_back(a);
		}
		flag=false;
		dfs(v);
		if(flag)printf("yes\n");
		else printf("no\n");
	}
	return 0;
}
