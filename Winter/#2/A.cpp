#include<iostream>
#include<cstring>
#include<string>
#include<vector>
#include<cstdio>
using namespace std;

char change(char a){
	if(a=='R')return 'P';
	if(a=='P')return 'S';
	if(a=='S')return 'R';
}

char dfs(long long x){
	if(x==1)return 'R';
	if(x==2)return 'P';
	if(x==3)return 'S';
	long long t=1;
	while(t<x)t*=3;
	return change(dfs(x-t/3));
}

int main(){
	long long n;
	while(true){
		scanf("%I64u",&n);
		if(n==0)break;
		printf("%c\n",change(dfs(n)));
	}
	return 0;
}
