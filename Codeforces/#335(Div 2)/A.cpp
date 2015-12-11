#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

int a[3];
int b[3];

int x,y;

int main(){
	for(int i=0;i<3;i++)cin>>a[i];
	for(int i=0;i<3;i++)cin>>b[i];
	for(int i=0;i<3;i++){
		int t=a[i]-b[i];
		if(t>0)x+=t/2;
		else y+=-t;
	}
	if(x>=y)cout<<"Yes"<<endl;
	else cout<<"No"<<endl;
	return 0;
}
