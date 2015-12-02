#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#define MAX_N 100005
using namespace std;

int n,k;
int a[MAX_N];

int cnt=0;

int main(){
	cin.sync_with_stdio(false);
	cin>>n>>k;
	int x=0;
	for(int i=0;i<n;i++)if(a[i]%k==0)cnt++;
	if(cnt%2==0)cout<<"Kevin"<<endl;
	else cout<<"Nicky"<<endl;
	
	return 0;
}
