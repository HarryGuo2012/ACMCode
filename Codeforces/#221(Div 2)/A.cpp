#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<string>
using namespace std;

string s;
int p;

int main(){
	cin.sync_with_stdio(false);
	cin>>s;
	while(s[p]!='^')p++;
	long long L=0,R=0;

	for(int i=0;i<s.length();i++){
		if(s[i]<='9'&&s[i]>='0'){
			if(i<p)L=L+(long long)(p-i)*(s[i]-'0');
			else R=R+(long long)(i-p)*(s[i]-'0');
		}		
	}
	if(L==R)
		cout<<"balance"<<endl;
	else if(L>R)
		cout<<"left"<<endl;
	else
		cout<<"right"<<endl;
	return 0;
}
