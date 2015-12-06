#include<iostream>
#include<cstring>
#include<queue>
#include<string>
using namespace std;

int n;

string a,b;

int main(){
	cin.sync_with_stdio(false);
	int T;
	cin>>T;
	while(T--){
		cin>>n;
		cin>>a>>b;
		bool flag=true;
		for(int i=0;i<n;i++){
			if(a[i]=='A'&&b[i]!='U')flag=false;
			if(a[i]=='C'&&b[i]!='G')flag=false;
			if(a[i]=='G'&&b[i]!='C')flag=false;
			if(a[i]=='T'&&b[i]!='A')flag=false;
			if(!flag)break;
		}
		if(flag)cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
	}
	return 0;
}
