#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#include <algorithm>
using namespace std;

char g[5555][2];
int a[5555],b[5555];

int n;

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%s",g[i]);
		scanf("%d%d",&a[i],&b[i]);
	}
	int ans=0;
	for(int i=1;i<=366;i++){
		int x=0,y=0;
		for(int j=1;j<=n;j++){
			if(i<a[j]||i>b[j])continue;
			if(g[j][0]=='F')x++;
			if(g[j][0]=='M')y++;
		}
		int m=min(x,y);
		ans=max(ans,m*2);
	}
	cout<<ans<<endl;
	//cin>>n;
	return 0;
}