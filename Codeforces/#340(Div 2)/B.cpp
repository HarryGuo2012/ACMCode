#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long ll;
int n;

ll ans=1;
bool haveOne=false;

ll cnt=0;

int main(){
	cin>>n;
	while(n--){
		bool a;
		cin>>a;
		if(a){
			if(haveOne)ans*=(cnt+1);
			haveOne=true;
			cnt=0;
		}
		else cnt++;
	}
	cout<<ans*haveOne<<endl;
	return 0;
}