#include <iostream>
#include <string>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

int n,k;
string s;
vector<char> ans;

int main(){
	cin.sync_with_stdio(false);
	cin>>n>>k>>s;
	for(int i=0;i<s.length();i++){
		char now='z';
		if(abs(now-s[i])<abs('a'-s[i]))now='a';
		if(k>abs(now-s[i])){ans.push_back(now);k-=abs(now-s[i]);}
		else{
			if(s[i]+k>'z')ans.push_back(s[i]-k);
			else ans.push_back(s[i]+k);
			k=0;
		}
	}
	if(k)cout<<-1<<endl;
	else{
		for(int i=0;i<ans.size();i++)
			cout<<ans[i];
		cout<<endl;
	}
	//cin>>n;
	return 0;
}