#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long ll;
ll n;

int main(){
	ll i=1,a=0;
	cin>>n;
	while(a<n){
		a+=i;
		i++;
	}
	i--;
	cout<<i+n-a<<endl;
	return 0;
}