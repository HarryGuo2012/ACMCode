#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
#include<set>
#include<algorithm>
#include<cstdio>
#define MAX_N 100005
using namespace std;

struct node{
	int x,y;
};

node a[MAX_N],b[MAX_N];
bool cmp(node u,node v){
	return u.y>v.y;
}

long long ans=0;

multiset<int> se;

int main(){
	int N,M;
	scanf("%d%d",&N,&M);
	for(int i=0;i<N;i++)
		scanf("%d%d",&a[i].x,&a[i].y);
	for(int i=0;i<M;i++)
		scanf("%d%d",&b[i].x,&b[i].y);
	sort(a,a+N,cmp);
	sort(b,b+M,cmp);
	int j=0;
	for(int i=0;i<N;i++){
		while(j!=M&&a[i].y<=b[j].y){
			se.insert(b[j].x);
			j++;
		}
		multiset<int>::iterator it=se.lower_bound(a[i].x);
		if(it==se.end()){ans=-1;break;}
		ans=ans+*it;
		se.erase(it);
	}
	printf("%I64d\n",ans);
	return 0;
}
