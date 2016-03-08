#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
#include<cstdio>
#include<algorithm>
#define MAX_N 26
using namespace std;

string s;
int n;

int a[MAX_N];
bool vis[MAX_N];
vector<int> v;

void ran(){
	random_shuffle(v.begin(),v.end());
	int j=0;
	for(int i=0;i<26;i++)
		if(vis[i])
			a[i]=v[j++];
}

int T;

int cnt;

int main(){
	for(int i=0;i<9;i++)
		v.push_back(i);
	cin>>T;
	while(T--){
		memset(vis,0,sizeof(vis));
		memset(a,0,sizeof(a));
		string s;
		cin>>s;
		for(int i=0;i<s.length();i++)
			if(!vis[s[i]-'a'])cnt++,vis[s[i]-'a']=1;
			
	}
	return 0;
}
