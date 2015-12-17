#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;

int a;
string single[23]={"zero","one","two","three","four","five","six","seven","eight","nine","ten","eleven","twelve","thirteen","fourteen","fifteen","sixteen","seventeen","eighteen","nineteen"};
string ten[23]={"","","twenty","thirty","forty","fifty","sixty","seventy","eighty","ninety"};

int main(){
	cin>>a;
	if(a<20)
		cout<<single[a]<<endl;
	else if(a%10)
		cout<<ten[a/10]<<"-"<<single[a%10]<<endl;
	else
		cout<<ten[a/10]<<endl;
	return 0;
}
