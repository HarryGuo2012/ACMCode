#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

string s;

int main(){
	getline(cin,s);
	int cnt=0;
	bool flag=false;
	for(int i=0;i<s.length();i++){
		if(s[i]=='('){
			if(flag)cnt++;
			flag=true;
		}
		else if(s[i]==')'){
			if(!flag)cnt++;
			flag=false;
		}
		else if((s[i]>='A'&&s[i]<='Z')||(s[i]>='a'&&s[i]<='z')||(s[i]==' '))
			continue;
		else if(flag)
			cnt++,flag=false;
	}
	if(flag)cnt++;
	cout<<cnt<<endl;
	return 0;
}
