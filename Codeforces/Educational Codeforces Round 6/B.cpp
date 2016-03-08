#include <iostream>
#include <cstring>
using namespace std;

int a[10]={6,2,5,5,4,5,6,3,7,6};

long long sum=0;

void Div(int x){
	while(x){
		int t=x%10;
		sum+=a[t];
		x/=10;
	}
}

int main(){
	int x,y;
	cin>>x>>y;
	for(int i=x;i<=y;i++)
		Div(i);
	cout<<sum<<endl;
	return 0;
}