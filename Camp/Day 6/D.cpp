#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstdio>
#define MAX_N 100005
using namespace std;

struct node{
	int a,b;
}v[MAX_N];

typedef long long ll;
bool cmp(node x,node y){
	if(x.a==y.a)return x.b<y.b;
	return x.a<y.a;
}

int n;

priority_queue<long long> que;

long long ans=0;
char cc;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d%d",&v[i].a,&v[i].b);
	sort(v+1,v+1+n,cmp);
	for(int i=1;i<n;i+=2){
		que.push(v[i].b);
		if(i+1!=n)
			que.push(v[i+1].b);
		long long now=que.top();que.pop();
		ans+=now;
	}
	cout<<ans<<endl;
	//cin>>cc;
	return 0;
}