#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
using namespace std;

string s;

int I,V,X,L,C,D,M;
int I1,V1,X1,L1,C1,D1,M1;

string change(int num) {
	string c[4][10]={{"0","I","II","III","IV","V","VI","VII","VIII","IX"},{"0","X","XX","XXX","XL","L","LX"
	,"LXX","LXXX","XC"},{"0","C","CC","CCC","CD","D",
	"DC","DCC","DCCC","CM"},{"0","M","MM","MMM"}};
	int t=1;
	int tmp=num;
	string st;
	if(tmp/1000!=0) st+=c[3][tmp/1000];
	if((tmp%1000)/100!=0) st+=c[2][(tmp%1000)/100];
	if((tmp%100)/10!=0) st+=c[1][(tmp%100)/10];
	if(tmp%10!=0) st+=c[0][tmp%10];
	return st;
}
string ans;

int cnt(char c,string ss){
	int res=0;
	for(int i=0;i<ss.length();i++)if(ss[i]==c||ss[i]==c-'A'+'a')res++;
	return res;
}

string tmp="IVXLCDM";

int main(){
	cin>>s;
	for(int i=1;i<=4000;i++){
		string now=change(i);
		bool flag=true;
		for(int j=0;j<tmp.length();j++)
			if(cnt(tmp[j],now)>cnt(tmp[j],s)){
				flag=false;
				break;
			}
		if(flag&&now.length()>=ans.length())ans=now;
	}
	cout<<ans<<endl;
	//cin>>tmp;
	return 0;
}