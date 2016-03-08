#include <iostream>
#include <cstring>
#include <string>
using namespace std;

string s;

int main(){
	long long ans=0;
	//cin.sync_with_stdio(false);
	cin>>s;
	for(int i=0;i<s.length();i++){
		int u=s[i]-'0';
		if(u%4==0)ans++;
		if(i>0){
			int v=s[i-1]-'0';
			if((v*10+u)%4==0)ans+=i;
		}
	}
	cout<<ans<<endl;
	return 0;
}