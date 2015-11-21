#include<iostream>
#include<cstring>
#define MAX_N 100005
using namespace std;

bool hasSame[MAX_N];
int pos[MAX_N];
int aa[MAX_N];

int main(){
	int n,m;
	cin.sync_with_stdio(false);
	cin>>n>>m;
	bool a=false,im=false;
	for(int i=1;i<=n;i++){
		int f;
		cin>>f;
		if(pos[f])hasSame[f]=1;
		else pos[f]=i;
	}
	for(int i=1;i<=m;i++){
		int b;
		cin>>b;
		if(hasSame[b])a=true;
		if(pos[b]==0)im=true;
		aa[i]=pos[b];
	}

	if(im)cout<<"Impossible"<<endl;
	else if(a)cout<<"Ambiguity"<<endl;
	else{
		cout<<"Possible"<<endl;
		for(int i=1;i<=m;i++)cout<<aa[i]<<" ";
		cout<<endl;
	}
	return 0;
}
