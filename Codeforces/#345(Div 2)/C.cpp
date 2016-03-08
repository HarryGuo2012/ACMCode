#include <iostream>
#include <cstring>
#include <cstdio>
#include <map>
using namespace std;

int n;
map<int,long long> x,y;
map<pair<int,int>,long long> ma;

int main(){
	cin.sync_with_stdio(false);
	cin>>n;
	for(int i=0;i<n;i++){
		int u,v;
		cin>>u>>v;
		x[u]++;y[v]++;
		ma[make_pair(u,v)]++;
	}
	map<int,long long>::iterator it;
	long long ans=0;
	for(it=x.begin();it!=x.end();it++){
		long long u=it->second;
		ans=ans+u*(u-1)/2;
	}
	for(it=y.begin();it!=y.end();it++){
		long long u=it->second;
		ans=ans+u*(u-1)/2;
	}
	map<pair<int,int>,long long>::iterator it2;
	for(it2=ma.begin();it2!=ma.end();it2++){
		long long u=it2->second;
		ans=ans-u*(u-1)/2;
	}
	cout<<ans<<endl;//cin>>n;
	return 0;
}