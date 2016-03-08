#include<iostream>
#include<cstring>
#include<vector>
#include<cstdio>
#define MAX_N 1234
using namespace std;

int t[MAX_N];
int n,s;

int main(){
	scanf("%d%d",&n,&s);
	for(int i=0;i<n;i++){
		int a,b;
		scanf("%d%d",&a,&b);
		t[a]=max(t[a],b);
	}
	int now=0;
	for(int i=s;i>=1;i--){
		if(t[i]>now)now=t[i];
		now++;
	}
	cout<<now<<endl;
	return 0;
}
