#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

typedef long long ll;

int n,m;
ll a,b;

ll x,y;

int main(){
	cin.sync_with_stdio(false);
	cin>>n>>a;
	ll tmp=1;
	for(int i=0;i<n-1;i++)tmp*=a;
	for(int i=0;i<n;i++){
		ll t;
		cin>>t;
		x+=t*tmp;
		tmp/=a;
	}
	cin>>m>>b;
	tmp=1;
	for(int i=0;i<m-1;i++)tmp*=b;
	for(int i=0;i<m;i++){
		ll t;
		cin>>t;
		y+=t*tmp;
		tmp/=b;
	}
	if(x>y)cout<<">"<<endl;
	else if(x==y)cout<<"="<<endl;
	else cout<<"<"<<endl;
	return 0;
}
