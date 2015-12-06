#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;

int n,T;

int main(){
	cin.sync_with_stdio(false);
	cin>>T;
	while(T--){
		cin>>n;
		cout<<(n&1)<<endl;
	}
	return 0;
}
