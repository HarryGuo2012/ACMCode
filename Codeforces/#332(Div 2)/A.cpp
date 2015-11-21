#include<iostream>
#include<algorithm>
using namespace std;

int a,b,c;

int main(){
	cin>>a>>b>>c;
	cout<<min(min(a+b+c,a*2+b*2),min(a*2+c*2,b*2+c*2))<<endl;
	return 0;
}
