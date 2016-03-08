#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <queue>
#define MAX_N 123
using namespace std;

queue<int> t[2];
int T,N,L;

string na[MAX_N];
int a[MAX_N];
char dir[MAX_N];
int sumL[MAX_N],sumR[MAX_N];
int ans[MAX_N];

int GetDir(int x){
	if(dir[x]=='L'){
		if(sumR[x]<=sumL[N]-sumL[x])return 0;
		else return 1;
	}
	else{
		if(sumL[x]<=sumR[N]-sumR[x])return 0;
		else return 1;
	}
}

int main(){
	cin.sync_with_stdio(false);
	scanf("%d",&T);
	while(T--){
		while(tL.size())tL.pop();
		while(tR.size())tR.pop();
		memset(sumL,0,sizeof(sumL));
		memset(sumR,0,sizeof(sumR));
		for(int i=1;i<=N;i++){
			cin>>na[i]>>a[i]>>dir[i];
			if(dir[i]=='R')
				a[i]=L-a[i];
		}
		for(int i=1;i<=N;i++)
			if(dir[i]=='L')t[0].push(a[i]);
		for(int i=N;i>=1;i--)
			if(dir[i]=='R')t[1].push(a[i]);
		for(int i=1;i<=N;i++){
			sumL[i]=sumL[i-1],sumR[i]=sumR[i-1];
			if(dir[i]=='L')sumL[i]++;
			if(dir[i]=='R')sumR[i]++;
		}
		int i=1,j=N;
		while(i<=j){
			int u=GetDir(i),v=GetDir(j);
		}
	}
	return 0;
}