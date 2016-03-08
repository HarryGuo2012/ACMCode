#include <iostream>
#include <cstring>
#include <vector>
#include <string>
#include <algorithm>
#define MAX_N 100005
using namespace std;

struct node{
	int x;char c;
	node(){}
	node(int xx,int cc):x(xx),c(cc){}
	bool operator==(node a){
		return x==a.x&&c=a.c;
	}
	bool operator!=(node a){
		return !(*this==a)
	}
};

vector<node> a,b;

int Next[MAX_N];

void getNext(){
	int i=0,j=-1;
	while(i<b.size()){
		while(j==-1||b[i]==b[j]){
			Next[i]=j;
			++i,++j;
		}
		j=Next[j];
	}
}

int KMP(){
	int cnt=0;
	getNext();
	int j=0;
	for(int i=0;i<a.size();i++){
		while(j&&b[j]!=a[i])j=Next[j];
		if(b[j]==a[i])j++;
		if(j==b.size())cnt++;
	}
	return cnt;
}

int n,m;

int main(){
	cin.sync_with_stdio(false);
	cin>>n>>m;
	for(int i=0;i<n;i++){
		string s,t;
		cin>>s;
		t.assign(s.begin(),s.begin()+s.length()-2);
		a.push_back(node(stoi(t,nullptr,0),s[s.length()-1]));
	}
	for(int i=0;i<m;i++){
		string s,t;
		cin>>s;
		t.assign(s.begin(),s.begin()+s.length()-2);
		b.push_back(node(stoi(t,nullptr,0),s[s.length()-1]));
	}
	return 0;
}