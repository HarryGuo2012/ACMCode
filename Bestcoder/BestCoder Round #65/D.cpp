//#include<iostream>
#include<fstream>
using namespace std;

int main(){
	int N=50000;
	ofstream cout("haha.txt");
	cout<<1<<"\n"<<N<<endl;
	long long sum=0;
	for(int i=1;i<=N;i++,sum+=i-1)
		cout<<sum<<" ";
	cout<<endl;
	return 0;
}
