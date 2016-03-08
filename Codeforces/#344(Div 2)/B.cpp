#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#define MAX_N 5555
using namespace std;

int n,m;
int x[MAX_N],y[MAX_N];
int tx[MAX_N],ty[MAX_N];

int main(){
	cin.sync_with_stdio(false);
	cin>>n>>m;
	int k;cin>>k;
	for(int i=1;i<=k;i++){
		int t,f,a;
		cin>>t>>f>>a;
		if(t==1){
			x[f]=a;
			tx[f]=i;
		}
		else{
			y[f]=a;
			ty[f]=i;
		}
	}
	for(int i=1;i<=n;i++,cout<<endl)
		for(int j=1;j<=m;j++){
			if(tx[i]>ty[j])
				cout<<x[i];
			else
				cout<<y[j];
			cout<<" ";
		}
	return 0;
}