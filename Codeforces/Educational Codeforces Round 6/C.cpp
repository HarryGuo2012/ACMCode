#include <iostream>
#include <cstdio>
#include <set>
#include <algorithm>
#include <vector>
#define MAX_N 300005
using namespace std;

set<int> se;

int n,a[MAX_N];
vector<pair<int,int> > ans;

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	int p=-1;
	for(int i=1;i<=n;i++){
		if(se.find(a[i])!=se.end()){
			ans.push_back(make_pair(p,i));
			se.clear();
			p=i+1;
		}
		else
			se.insert(a[i]);
	}
	if(ans.size()==0){
		printf("-1\n");
		return 0;
	}
	printf("%d\n",(int)ans.size());
	for(int i=0;i<ans.size();i++)
		printf("%d %d\n",ans[i].first,ans[i].second);
	return 0;
}