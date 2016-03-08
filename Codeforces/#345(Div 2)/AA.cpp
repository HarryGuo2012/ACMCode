#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;

int a,b;

int work(int x,int y){
	int u=min(x,y),v=max(x,y);
	if(v==1)return 0;
	int t=v/2;
	if(v%2==0)t--;
	if(t==0)return 1;
	return t+work(u+t,v-2*t);
}

int main(){
	cin>>a>>b;
	cout<<work(a,b)<<endl;
	return 0;
}