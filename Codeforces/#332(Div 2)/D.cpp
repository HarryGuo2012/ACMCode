#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;

typedef long long ll;

ll f;

vector<pair<ll,ll> > v;

int main(){
	cin>>f;
	for(ll n=1;n*n*n<9*f||n<1e5;n++){
		ll A=n*n+n-(n+1)*n/2;
		ll b=n*n+n-(n+1)*n*n/2-(n+1)*n*2/2+n*(n+1)*(2*n+1)/6;
		ll t=f-b;
		if(t<=0)continue;
		if(t%A==0){
			ll m=t/A;
			if(m<n)continue;
			v.push_back(make_pair(n,m));	
			if(n!=m)v.push_back(make_pair(m,n));
		}
	}
	sort(v.begin(),v.end());
	cout<<v.size()<<endl;
	for(int i=0;i<v.size();i++)
		cout<<v[i].first<<" "<<v[i].second<<endl;
	return 0;
}
