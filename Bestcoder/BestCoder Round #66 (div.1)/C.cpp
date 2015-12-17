#include<iostream>
#include<cstring>
#include<vector>
#include<cstdio>
#include<algorithm>
using namespace std;

long long A;

long long dfs(long long L,long long R,int i){
	if(i==-1)return 1;
	bool t=(A>>i)&1;
	if((L>>i)&1){
		if(t)return 0;
		else return dfs(L,R,i-1);
	}
	if(((R>>i)&1)==0){
		if(t)return 0;
		else return dfs(L,R,i-1);
	}
	long long m=(R>>i)<<i;
	if(!t) return dfs(L,m-1,i-1)+dfs(m,R,i-1);
	else return dfs(L,m-1,i-1)*dfs(m,R,i-1);
}

int Te;
long long l,r,G,T;

int main(){
	scanf("%d",&Te);
	while(Te--){
		scanf("%I64d%I64d%I64d%I64d",&l,&r,&G,&T);
		A=G^T;
		long long cnt=dfs(l,r,60);
		printf("%I64d\n",2*(r-l+1)*cnt);
	}
	return 0;
}
