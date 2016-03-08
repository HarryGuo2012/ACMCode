#include <iostream>
using namespace std;

int a,b;
char c;

int all;

int main(){
	cin>>a>>c>>b;
	int m=a*60+b;
	int t;
	cin>>t;
	m+=t;
	all=24*60;
	m%=all;
	int h=m/60;
	m%=60;
	if(h<10)cout<<0;
	cout<<h<<":";
	if(m<10)cout<<0;
	cout<<m<<endl;
	return 0;
}