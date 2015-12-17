#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;

typedef long long ll;

vector<ll> v;

void dfs(ll now){
	if(now>1e9)return;
	v.push_back(now);
	dfs(now*10+4);
	dfs(now*10+7);
}

int main(){
	dfs(4);
	dfs(7);
	sort(v.begin(),v.end());
	ll n;
	cin>>n;
	int i=0;
	for(;i<v.size();i++)
		if(v[i]==n)break;
	cout<<i+1<<endl;
	return 0;
}
