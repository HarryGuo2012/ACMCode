#include<iostream>
#include<cstring>
#include<vector>
#include<cstdio>
#include<algorithm>
#include<queue>
#define MAX_S 1<<19
#define MAX_N 5555
using namespace std;

int cnt[MAX_S];
int start[MAX_N];
int to[MAX_N];

int tot;//number of trains

bool go[MAX_S];
int N;

int id[MAX_S];

void solve(){
	
	for(int i=1;;i++){
		for(int j=0;j<tot;j++){
			if(i<=start[j])continue;
			int h=(i-start[j]);
			if((1<<h)>=N)continue;
			bool now=(to[j]>>h)&1;
			if(now!=go[)
		}
	}
}

int main(){
	return 0;
}
