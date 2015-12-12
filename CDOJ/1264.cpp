#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
#include<cmath>
using namespace std;

int main(){
	int n;
	cin>>n;
	int i=0,t=1;
	while((t-1)/2<n)i++,t*=3;
	cout<<i<<endl;
	return 0;
}
