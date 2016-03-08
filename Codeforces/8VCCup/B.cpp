#include <iostream>
#include <string>
#include <algorithm>
#include <cstdio>
using namespace std;

int n;
string s;

int r,b,g;
bool rr=false,bb=false,gg=false;

void haha(){
	if(r&&b&&g)rr=bb=gg=1;
}

int main(){
	cin>>n>>s;
	for(int i=0;i<s.length();i++){
		if(s[i]=='R')r++;
		if(s[i]=='B')b++;
		if(s[i]=='G')g++;
	}
	if(r==0&&b==0){
		cout<<'G'<<endl;
		return 0;
	}
	if(r==0&&g==0){
		cout<<'B'<<endl;
		return 0;
	}
	if(g==0&&b==0){
		cout<<'R'<<endl;
		return 0;
	}
	haha();
	if(r>0&&b>0){
		gg=true;
		r--;b--;g++;
	}
	haha();
	if(b>0&&g>0){
		rr=true;
		b--;g--;r++;
	}
	haha();
	if(g>0&&r>0){
		g--;r--;b++;
		bb=true;
	}
	haha();
	if(r>0&&b>0){
		gg=true;
		r--;b--;g++;
	}
	haha();
	if(b>0&&g>0){
		rr=true;
		b--;g--;r++;
	}
	haha();
	if(g>0&&r>0){
		g--;r--;b++;
		bb=true;
	}
	haha();
	if(bb)cout<<'B';
	if(gg)cout<<'G';
	if(rr)cout<<'R';
	cout<<endl;
	return 0;
}