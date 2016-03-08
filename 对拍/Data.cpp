#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <ctime>
#include <cstdlib>
using namespace std;

int n;

int main(){
	srand(time(0));
	n=rand()%100+1;
	cout<<n<<endl;
	for(int i=2;i<=n;i++){
		int t=rand()%(i-1)+1;
		cout<<i<<" "<<t<<endl;
	}
	return 0;
}