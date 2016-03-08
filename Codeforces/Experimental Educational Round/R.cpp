#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

long long n;

int main(){
	cin>>n;
	if(n&1)cout<<1<<endl;
	else cout<<2<<endl;
	return 0;
}