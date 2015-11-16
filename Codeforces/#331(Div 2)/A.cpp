#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;

int n;
int x[4],y[4];

int maxX,minX,maxY,minY;

int main(){
	cin>>n;
	for(int i=0;i<n;i++)cin>>x[i]>>y[i];
	if(n==1){
		cout<<-1<<endl;
		return 0;
	}
	if(n==2){
		if(x[0]!=x[1]&&y[0]!=y[1])
			cout<<abs(x[0]-x[1])*abs(y[0]-y[1])<<endl;
		else
			cout<<-1<<endl;
		return 0;
	}
	maxX=maxY=-2000;
	minX=minY=2000;
	for(int i=0;i<n;i++){
		maxX=max(maxX,x[i]);
		maxY=max(maxY,y[i]);
		minX=min(minX,x[i]);
		minY=min(minY,y[i]);
	}
	cout<<(maxX-minX)*(maxY-minY)<<endl;
	return 0;
}
