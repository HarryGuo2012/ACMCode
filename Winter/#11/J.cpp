#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <map>
#include <vector>
#include <string>
#define MAX_N 100005
using namespace std;

vector<string> vs;
int n,m;
int sx,sy,tx,ty;

string s;

vector<bool> dp0[MAX_N],dp1[MAX_N];

int main(){
	cin.sync_with_stdio(false);
	cin>>n>>m;
	for(int i=0;i<vs.size();i++){
		cin>>s;
		vs.push_back(s);
	}
	for(int i=0;i<n;i++){
		dp0[i].resize(m,0);
		dp1[i].resize(m,0);
	}
	
	return 0;
}