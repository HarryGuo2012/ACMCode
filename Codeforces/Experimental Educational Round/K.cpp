#include <iostream>
#include <algorithm>
using namespace std;

long long n;
int main(){
	cin>>n;
	long long _2=n/2,_3=n/3,_5=n/5,_7=n/7;
	long long _23=n/6,_25=n/10,_27=n/14,_35=n/15,_37=n/21,_57=n/35;
	long long _357=n/(3*5*7),_257=n/(2*5*7),_235=n/(2*3*5),_237=n/(2*3*7);
	long long _2357=n/(2*3*5*7);
	cout<<n-_2-_3-_5-_7+_23+_25+_27+_35+_37+_57-_357-_257-_237-_235+_2357<<endl;
	return 0;
}