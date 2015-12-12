#include<iostream>
#include<cstring>
#include<string>
using namespace std;

int i=0,j=0,k=0;

char now='1';
bool sign=true;

int main(){
	int n,m;
	string s;
	cin.sync_with_stdio(false);
	cin>>n>>m>>s;
	for(auto c:s){
		switch(c){
			case 'i':
				if(now=='1')now='i';
				else if(now=='i')now='1',sign^=1;
				else if(now=='j')now='k',sign^=1;
				else if(now=='k')now='j';
				i++;
				break;
			case 'j':
				if(now=='1')now='j';
				else if(now=='i')now='k';
				else if(now=='j')now='1',sign^=1;
				else if(now=='k')now='i',sign^=1;
				j++;
				break;
			case 'k':
				if(now=='1')now='k';
				else if(now=='i')now='j',sign^=1;
				else if(now=='j')now='i';
				else if(now=='k')now='1',sign^=1;
				k++;
				break;
		}
	}
	if(now=='1'&&sign==1){
		cout<<0<<endl;
		return 0;
	}
	if(m==0||now!='1'){
		cout<<-1<<endl;
		return 0;
	}
	if(i==n||j==n||k==n)cout<<-1<<endl;
	else cout<<1<<endl;
	return 0;
}
