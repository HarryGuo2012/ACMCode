#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
#define MAX_N 50004
using namespace std;

string s[MAX_N];

int n;

bool cmp(string x,string y){
	string t1,t2;
	t1=x+y;
	t2=y+x;
	return t1<t2;
}

int main(){
	cin.sync_with_stdio(false);
	cin>>n;
	for(int i=0;i<n;i++)
		cin>>s[i];
	sort(s,s+n,cmp);
	for(int i=0;i<n;i++)
		cout<<s[i];
	cout<<endl;
	//cin>>n;
	return 0;
}