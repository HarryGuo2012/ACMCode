#include <string>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

string str;

vector<string> vs;

bool check[6];

bool jiggle(int x){
	if(x<0||x>=vs.size())return false;
	return vs[x]=="jiggle";
}

bool twirl(int x){
	if(x<0||x>=vs.size())return false;
	return vs[x]=="twirl";
}

void check1(){
	for(int i=0;i<vs.size();i++)
		if(vs[i]=="dip"){
			if(jiggle(i-1)||jiggle(i-2)||twirl(i+1)||twirl(i+2)) continue;
			check[1]=0;
			vs[i]="DIP";
		}
}

void check2(){
	if(vs.size()<3){
		check[2]=false;
		return;
	}
	check[2]=vs[vs.size()-1]=="clap"&&vs[vs.size()-2]=="stomp"&&vs[vs.size()-3]=="clap";
}

void check3(){
	bool haveTwirl=false;
	for(int i=0;i<vs.size();i++)if(vs[i]=="twirl"){
		haveTwirl=true;
		break;
	}
	if(!haveTwirl)return;
	if(haveTwirl)for(int i=0;i<vs.size();i++)if(vs[i]=="hop")return;
	check[3]=false;
}

void check4(){
	if(vs.size()>0&&vs[0]=="jiggle")
		check[4]=false;
}

void check5(){
	for(int i=0;i<vs.size();i++)if(vs[i]=="dip"||vs[i]=="DIP")return;
	check[5]=false;
}

string tmp;
vector<int> er;

int main(){
	while(getline(cin,str)){
		memset(check,1,sizeof(check));
		vs.clear();er.clear();
		istringstream istr(str);
		while(istr>>tmp)
			vs.push_back(tmp);
		check1();
		check2();
		check3();
		check4();
		check5();
		for(int i=1;i<=5;i++)
			if(check[i]==0)
				er.push_back(i);
		if(er.size()==0){
			cout<<"form ok: "<<str<<endl;
			continue;
		}
		if(er.size()==1){
			cout<<"form error "<<er[0]<<":";
			for(int i=0;i<vs.size();i++)
				cout<<" "<<vs[i];
			cout<<endl;
			continue;
		}
		cout<<"form errors";
		sort(er.begin(),er.end());
		for(int i=0;i<er.size();i++){
			if(i==0)
				cout<<" ";
			else if(i==er.size()-1)
				cout<<" and ";
			else
				cout<<", ";
			cout<<er[i];
		}
		cout<<":";
		for(int i=0;i<vs.size();i++)
			cout<<" "<<vs[i];
		cout<<endl;
	}
	return 0;
}