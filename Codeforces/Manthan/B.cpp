#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

typedef long long ll;

ll m;

ll Get(ll x){
	ll res=0;
	while(x%5==0){
		res++;
		x/=5;
	}
	return res;
}

int main(){
	cin>>m;
	ll cnt=0;
	for(ll i=5;cnt<=m;i+=5){
		cnt+=Get(i);
		if(cnt==m){
			cout<<5<<endl;
			for(int j=0;j<5;j++)cout<<j+i<<" ";
			cout<<endl;
			//cin>>m;
			return 0;
		}
	}
	cout<<0<<endl;
	return 0;
}