#include<iostream>
#include<cstring>
#include<vector>
#include<cstdio>
#include<algorithm>
#define MAX_N 1003
using namespace std;

struct Line{
	int L,R;
	Line(int LL,int RR):L(LL),R(RR){}
	Line(){}
}a[MAX_N];

bool vis[MAX_N];

int n;
int m;

bool cross(int i,int j){
	if(a[i].L>a[j].R)return false;
	if(a[i].R<a[j].L)return false;
	return true;
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
		scanf("%d%d",&a[i].L,&a[i].R);
	bool update=true;
	while(update){
		update=false;
		for(int i=1;i<=m;i++){
			if(vis[i])continue;
			for(int j=1;j<=m;j++){
				if(i==j||vis[j])continue;
				if(cross(i,j)){
					update=true;
					a[i].L=min(a[i].L,a[j].L);
					a[i].R=max(a[i].R,a[j].R);
					vis[j]=1;
				}
			}
		}
	}
	int ans=0;
	for(int i=1;i<=m;i++)
		if(!vis[i])
			ans+=a[i].R-a[i].L;
	cout<<ans*2+n+1<<endl;
	return 0;
}
