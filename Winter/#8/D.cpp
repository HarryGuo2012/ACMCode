#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <set>
#include <cstdio>
#define MAX_N 200005
using namespace std;

int N,M;

struct Point{
	int x,y;
	Point(int xx,int yy):x(xx),y(yy){}
	Point(){}
};

Point P[MAX_N];

vector<int> xTmp,yTmp;
vector<int> xL,yL;

vector<int> xG[MAX_N],yG[MAX_N];

void init(){
	xTmp.clear();
	yTmp.clear();
	xL.clear();
	yL.clear();
	for(int i=0;i<MAX_N;i++)
		xG[i].clear();
	for(int i=0;i<MAX_N;i++)
		yG[i].clear();
}

int main(){
	while(scanf("%d%d",&N,&M)==2){
		if(N==0&&M==0)break;
		init();
		for(int i=0;i<N;i++){
			int x,y;
			scanf("%d%d",&x,&y);
			P[i]=Point(x,y);
			xTmp.push_back(x);
			yTmp.push_back(y);
		}
		getchar();
		for(int i=0;i<M;i++){
			char c;
			int val;
			scanf("%c=%d",&c,&val);
			if(c=='x'){
				xL.push_back(val);
				xTmp.push_back(val);
			}
			else{
				yL.push_back(val);
				yTmp.push_back(val);
			}
			getchar();
		}

		sort(xTmp.begin(),xTmp.end());
		sort(yTmp.begin(),yTmp.end());

		vector<int>::iterator it=unique(xTmp.begin(),xTmp.end());
		xTmp.resize(distance(xTmp.begin(),it));
		it=unique(yTmp.begin(),yTmp.end());
		yTmp.resize(distance(yTmp.begin(),it));
		
		for(int i=0;i<N;i++){
			P[i].x=lower_bound(xTmp.begin(),xTmp.end(),P[i].x)-xTmp.begin();
			P[i].y=lower_bound(yTmp.begin(),yTmp.end(),P[i].y)-yTmp.begin();
			xG[P[i].x].push_back(P[i].y);
			yG[P[i].y].push_back(P[i].x);
		}
		for(int i=0;i<xL.size();i++)
			xL[i]=lower_bound(xTmp.begin(),xTmp.end(),xL[i])-xTmp.begin();
		for(int i=0;i<yL.size();i++)
			yL[i]=lower_bound(yTmp.begin(),yTmp.end(),yL[i])-yTmp.begin();
		
		sort(xL.begin(),xL.end());
		sort(yL.begin(),yL.end());

		for(int i=0;i<MAX_N;i++)
			sort(xG[i].begin(),xG[i].end());
		for(int i=0;i<MAX_N;i++)
			sort(yG[i].begin(),yG[i].end());

		int cnt=0;
		for(int i=0;i<N;i++){
			int x=P[i].x,y=P[i].y;
			int px=-1,nx=MAX_N,py=-1,ny=MAX_N;
			int u=lower_bound(yG[y].begin(),yG[y].end(),x)-yG[y].begin();
			int v=lower_bound(xG[x].begin(),xG[x].end(),y)-xG[x].begin();
			if(u!=0)px=yG[y][u-1];
			if(u!=yG[y].size()-1)nx=yG[y][u+1];
			if(v!=0)py=xG[x][v-1];
			if(v!=xG[x].size()-1)ny=xG[x][v+1];

			bool flag=false;

			int plx,nlx,ply,nly;
			vector<int>::iterator it;
			it=lower_bound(xL.begin(),xL.end(),x);
			if(it!=xL.end()&&*it<nx)flag=true;
			if(it!=xL.begin()&&*(--it)>px)flag=true;
			it=lower_bound(yL.begin(),yL.end(),y);
			if(it!=yL.end()&&*it<ny)flag=true;
			if(it!=yL.begin()&&*(--it)>py)flag=true;

			cnt+=flag;
		}
		printf("%d\n",cnt);
	}
	return 0;
}