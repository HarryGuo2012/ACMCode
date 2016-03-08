#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <queue>
#include <string>
#define MAX_N 222
using namespace std;

int u[MAX_N],d[MAX_N],r[MAX_N],l[MAX_N];
string s;

int main(){
	int n;cin>>n>>s;
	for(int i=1;i<=n;i++){
		u[i]=u[i-1],r[i]=r[i-1],l[i]=l[i-1],d[i]=d[i-1];
		if(s[i-1]=='U')u[i]=u[i-1]+1;
		if(s[i-1]=='R')r[i]=r[i-1]+1;
		if(s[i-1]=='L')l[i]=l[i-1]+1;
		if(s[i-1]=='D')d[i]=d[i-1]+1;
	}
	int ans=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<i;j++)
			if(r[i]-r[j-1]==l[i]-l[j-1]&&u[i]-u[j-1]==d[i]-d[j-1])
				ans++;
	cout<<ans<<endl;
	return 0;
}