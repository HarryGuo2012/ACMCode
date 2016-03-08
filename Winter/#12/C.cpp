#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

long long P1,P2;

int main(){
	cin>>P1>>P2;
	int i=1;
	while(P1>=0){
		long long tmp=P1-P2;
		P1=P2;
		P2=tmp;
		if(P1==0&&P2==0){
			cout<<0<<" "<<0<<endl;
			return 0;
		}
		i++;
	}
	cout<<i<<" "<<P1<<endl;
	//cin>>i;
	return 0;
}