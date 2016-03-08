#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#define MAX_N 500005
using namespace std;

int n,a,b,T;
string s;

int now;
int sum[MAX_N];

int cost(int x){
	if(s[x]=='w')return b+1;
	return 1;
}

int cost0(int x){
	return sum[x]+x*a;
}	

int cost1(int x){
	return sum[n-1]-sum[x-1]+(n-x)*a;
}

int bi0(int x){
	if(n==1||x==n-1||cost1(n-1)>now)return 0;
	int l=x,r=n-1;
	while(r-l>1){
		int mid=(l+r)>>1;
		if(cost1(mid)<=now)r=mid;
		else l=mid;
	}
	return n-r;
}

int bi1(int x){
	if(n==1||x==1||cost0(1)>now)return 0;
	int l=1,r=x;
	while(r-l>1){
		int mid=(l+r)>>1;
		if(cost0(mid)<=now)l=mid;
		else r=mid;
	}
	return l;
}

int main(){
	cin.sync_with_stdio(false);
	cin>>n>>a>>b>>T>>s;
	for(int i=1;i<s.length();i++)
		sum[i]=sum[i-1]+cost(i);
	if(T<cost(0)){
		cout<<0<<endl;
		return 0;
	}
	int ans=1;
	for(int i=1;i<s.length();i++){
		if(cost0(i)>T)break;
		now=T-cost0(i);
		now-=i*a;
		ans=max(ans,bi0(i)+i);
	}
	for(int i=s.length()-1;i>0;i--){
		if(cost1(i)>T)break;
		now=T-cost1(i);
		now-=(n-i)*a;
		ans=max(ans,bi1(i)+(n-i));
	}
	cout<<ans<<endl;cin>>n;
	return 0;
}