#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<cstdio>
#define MAX_N 555
using namespace std;

int n,m;
int a[MAX_N][MAX_N];

int main(){
	cin.sync_with_stdio(false);
	cin>>n>>m;
	for(int i=0;i<n;i++)
		for(int j=0;j<2*m;j++)
			cin>>a[i][j];
	int ans=0;
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++)ans+=a[i][2*j]|a[i][2*j+1];
	}
	cout<<ans<<endl;
	return 0;
}
