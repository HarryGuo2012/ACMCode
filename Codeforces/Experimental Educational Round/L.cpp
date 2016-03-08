#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

string s;
int t[5];

int main(){
	cin>>s;
	long long a=0;
	a=(s[0]-'0')*10000+(s[1]-'0')+(s[2]-'0')*1000+(s[3]-'0')*10+(s[4]-'0')*100;
	long long mod=100000;
	a=a*a%mod*a%mod*a%mod*a%mod;
	for(int i=0;i<5;i++)
		t[i]=a%10,a/=10;
	for(int i=4;i>=0;i--)
		cout<<t[i];
	cout<<endl;
	return 0;
}