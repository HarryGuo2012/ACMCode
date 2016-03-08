#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int a,b,c;

int main(){
	cin>>a>>b>>c;
	for(int x=0;x<c/a+3;x++){
		if(x*a>c)break;
		int r=c-x*a;
		if(r%b==0){
			cout<<"Yes"<<endl;
			return 0;
		}
	}
	cout<<"No"<<endl;
	return 0;
}