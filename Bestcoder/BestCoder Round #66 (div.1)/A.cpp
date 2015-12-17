#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cstdio>
#define MAX_N 50004
using namespace std;

int T;
int n,m;

struct node{
	bool group;
	int val;
};

node a[MAX_N];
int ma[2];

int tim[MAX_N];

int main(){
	scanf("%d",&T);
	while(T--){
		memset(tim,0,sizeof(tim));
		memset(ma,0,sizeof(ma));
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)
			scanf("%d%d",&a[i].group,&a[i].val);
		for(int i=0;i<m;i++){
			int t;
			scanf("%d",&t);
			tim[t]++;
		}
		int cnt=n;
		int now=0;
		for(int i=n;i>=1;i--){
			now+=tim[i];
			if(a[i].val+now<ma[!a[i].group])
				cnt--;
			ma[a[i].group]=max(ma[a[i].group],a[i].val+now);
		}
		printf("%d\n",cnt);
	}
	return 0;
}
