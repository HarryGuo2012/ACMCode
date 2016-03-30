#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int n,k;string s;

int main(){
	cin>>n>>k;
	for(int i=0;i<n;i++)
		cin>>s;
	for(int i=1;i<=n;i++)
		cout<<i<<" ";
	cout<<endl;
	return 0;
}