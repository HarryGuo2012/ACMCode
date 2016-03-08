#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
#include<map>
#include<string>
using namespace std;

map<string,string> ma;

string a,b;

int main(){
	cin.sync_with_stdio(false);
	int n,m;
	cin>>n>>m;
	while(m--){
		cin>>a>>b;
		if(a.length()>b.length())
			ma[a]=b;
		else
			ma[a]=a;
	}
	while(n--){
		cin>>a;
		cout<<ma[a]<<" ";
	}
	cout<<endl;
	return 0;
}
