#include <iostream>
#include <cstring>
#include <algorithm>
#define MAX_N 55
using namespace std;

int a[MAX_N][MAX_N];
int n;

bool vis[MAX_N];
int ans[MAX_N];

int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			cin>>a[i][j];
	
	for(int x=1;x<=n;x++){
		for(int y=1;y<=n;y++){
			if(vis[y])continue;
			bool flag=true;
			for(int i=1;i<=n;i++)
				if(a[i][y]>x){flag=false;break;}
			for(int j=1;j<=n;j++)
				if(a[y][j]>x){flag=false;break;}
			if(flag){
				//cout<<x<<" "<<y<<endl;
				vis[y]=1;
				ans[y]=x;
				break;
			}
		}
	}
	for(int i=1;i<=n;i++)
		cout<<ans[i]<<" ";
	cout<<endl;
	//char cc;
	//cin>>cc;
	return 0;
}