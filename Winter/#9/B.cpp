#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <string>
#define MAX_N 100005
using namespace std;

string s;

int a[MAX_N];

int f,s;

int main(){
	cin>>s;
	for(int i=0;i<s.length();i++)a[i+1]=s[i]-'0';
	int p=1;
	for(;p<=n;p++){
		if(a[p]==4)f++;
		else if(a[p]==7)s++;
		else break;
	}
	if(p!=n+1){
		if(a[p]<7&&a[p]>4)
			if(check(p,7))return 0;
		else if(a[p]<4){
			if(check(p,4))return 0;
			if(check(p,7))return 0;
		}
	}
	p--;
	for(;p>=1;p--){
		if(a[p]==4)if(check(p,7))return 0;
		if(a[p]==4)f--;
		if(a[p]==7)s--;
	}
	return 0;
}