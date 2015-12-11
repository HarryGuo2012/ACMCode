#include<iostream>
#include<cstring>
using namespace std;

int n,m;

int main(){
	cin>>n>>m;
	if(!(m&1))cout<<m+1<<".000000"<<endl;
	else cout<<"too young,too simple"<<endl;
	return 0;
}
