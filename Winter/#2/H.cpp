#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#define MAX_N 123
using namespace std;

vector<int> P[MAX_N];
vector<int> C[MAX_N];
vector<int> A[MAX_N];
vector<int> K;
int n;

bool convert(int x){
	for(int i=0;i<P[x].size();i++){
		int now;
		if(i<K.size())
			now=(P[x][i]+K[i])%26;
		else
			now=(P[x][i]+C[x][i-K.size()])%26;

		//if(x==0&&K.size()==3)cout<<now<<" ";
		if(now!=C[x][i])return false;
	}
	//cout<<endl;
	return true;
}

int maxA,mp;

void del(){
	for(int x=0;x<n;x++)
		for(int i=0;i<P[x].size();i++)
			A[x].push_back((C[x][i]-P[x][i]+26)%26);
	for(int x=0;x<n;x++){
		if(maxA<A[x].size())
			maxA=A[x].size(),mp=x;
	}
}

void clear(){
	maxA=0;
	for(int i=0;i<MAX_N;i++){
		P[i].clear();
		C[i].clear();
		A[i].clear();
	}
	K.clear();
}

string s,t;

void output(){
	for(int i=0;i<K.size();i++)
		cout<<(char)(K[i]+'A');
	cout<<endl;
}

void outputA(){
	for(int x=0;x<n;x++,cout<<endl)
		for(int i=0;i<A[x].size();i++)
			cout<<A[x][i]<<" ";
}

void outputC(){
	for(int x=0;x<n;x++,cout<<endl)
		for(int i=0;i<C[x].size();i++)
			cout<<C[x][i]<<" ";
}

int main(){
	//cin.sync_with_stdio(false);
	while(true){
		clear();
		cin>>n;
		if(n==0)break;
		for(int i=0;i<n;i++){
			cin>>s>>t;
			for(int j=0;j<s.length();j++)
				P[i].push_back(s[j]-'A');
			for(int j=0;j<t.length();j++)
				C[i].push_back(t[j]-'A');	
		}
		del();
	//	outputC();
	//	cout<<"-----"<<endl;
		bool flag=false;
		/*
		for(int x=0;x<n;x++)
			if(!convert(x)){
				flag=false;
				break;
			}
		if(flag){
			cout<<endl;
			continue;
		}
		*/
		for(int i=0;i<maxA;i++){
			int now=A[mp][i];
			for(int x=0;x<n;x++)
				if(i<A[x].size()&&now!=A[x][i])break;
			K.push_back(now);
			bool tmp=true;
			for(int x=0;x<n;x++){
				if(!convert(x)){
					tmp=false;
					break;
				}
			}
			if(tmp){
				flag=true;
				break;
			}
		}
		if(flag)
			output();
		else
			cout<<"Impossible"<<endl;
	}
	return 0;
}
