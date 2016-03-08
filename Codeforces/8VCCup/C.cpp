#include <iostream>
#include <cstring>
#include <vector>
#include <set>
#include <algorithm>
#define INF 3333333
using namespace std;

int n,m;

int ans=INF;

bool check(int x){
	int a=x/2,b=x/3,c=x/6;
	a-=c,b-=c;
	int u=n,v=m;
	u=max(0,u-a),v=max(0,v-b);
	return u+v<=c;
}

int main(){
	cin>>n>>m;
	int L=0,R=INF;
	while(R-L>1){
		int mid=(R+L)/2;
		if(check(mid))R=mid;
		else L=mid;
	}
	cout<<R<<endl;
	//cin>>n;
	return 0;
}