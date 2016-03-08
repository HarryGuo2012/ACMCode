//#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
#include<fstream>
using namespace std;

int w,h,x[5],y[5];

int main(){
	ifstream cin("grave.in");
	ofstream cout("grave.out");
	for(int i=1;i<=4;i++)
		cin>>x[i]>>y[i];
	cin>>w>>h;
	int mw=max(x[3]-x[1],x[2]-x[4]);
	int mh=max(y[3]-y[1],y[2]-y[4]);
	if(w<=mw&&h<=y[2]-y[1])
		cout<<"YES"<<endl;
	else if(h<=mh&&w<=x[2]-x[1])
		cout<<"YES"<<endl;
	else 
		cout<<"NO"<<endl;
	return 0;
}
