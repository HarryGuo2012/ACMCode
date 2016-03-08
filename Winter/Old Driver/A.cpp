#include <iostream>
#include <cstring>
using namespace std;

int x;

int main(){
	cin>>x;
	if(x==1){
		cout<<1<<endl;
		return 0;
	}
	if(x==3){
		cout<<5<<endl;
		return 0;
	}
	int i;
	for(i=3;i*i/2+1<x;i+=2);
	cout<<i<<endl;
	return 0;
}