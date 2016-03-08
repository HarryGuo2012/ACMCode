#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
#include<cstdio>
#define MAX_N 102
#define MAX_D 2003
using namespace std;

bool vis[MAX_N][MAX_N][MAX_D][4];
bool G[MAX_N][MAX_N];

int dx[4]={0,1,0,-1},dy[4]={1,0,-1,0};
int dir[MAX_D];

char cc;

void dfs(int x,int y,int s,int d){
	if(s==MAX_D)return;
	if(vis[x][y][s][d])return;
	vis[x][y][s][d]=1;
	if(d==dir[s]||dir[s]==-1){
		for(int i=0;i<4;i++){
			if(abs(d-i)==2)continue;
			int nx=x+dx[i],ny=y+dy[i];
			if(nx<0||nx>=MAX_N||ny<0||ny>=MAX_N||G[nx][ny]==false)continue;
			dfs(nx,ny,s+1,i);
		}
	}
	else{
		if(abs(dir[s]-d)==2)return;
		int nx=x+dx[dir[s]],ny=y+dy[dir[s]];
		if(nx<0||nx>=MAX_N||ny<0||ny>=MAX_N||G[nx][ny]==false)return;
		dfs(nx,ny,s+1,dir[s]);
	}
}

void draw(int xa,int ya,int xb,int yb){
	for(int i=min(xa,xb);i<=max(xa,xb);i++)
		for(int j=min(ya,yb);j<=max(ya,yb);j++)
			G[i][j]=1;
}

int n,x0,y0,t;

vector<pair<int,int> > ans;

int main(){
	memset(dir,-1,sizeof(dir));
	scanf("%d%d%d%d",&n,&x0,&y0,&t);
	for(int i=0;i<n;i++){
		int xa,ya,xb,yb;
		scanf("%d%d%d%d",&xa,&ya,&xb,&yb);
		draw(xa*2,ya*2,xb*2,yb*2);
	}
	x0*=2,y0*=2;
	int now=0;
	for(int i=1;i<=t;i++){
		int s;
		char c;
		cin>>s>>c;
		s*=2;
		now+=s;
		if(c=='N')dir[now]=0;
		if(c=='S')dir[now]=2;
		if(c=='E')dir[now]=1;
		if(c=='W')dir[now]=3;
	}
	bool f[2]={0,0};
	for(int i=0;i<4;i++){
		int nx=x0+dx[i],ny=y0+dy[i];
		if(nx<0||nx>=MAX_N||ny<0||ny>=MAX_N||G[nx][ny]==false)continue;
		f[i%2]=true;
	}
	if(f[0]){
		dfs(x0,y0,0,0);
		dfs(x0,y0,0,2);
	}
	if(f[1]){
		dfs(x0,y0,0,1);
		dfs(x0,y0,0,3);
	}
	for(int i=0;i<MAX_N;i++)
		for(int j=0;j<MAX_N;j++){
			if(vis[i][j][now][dir[now]])
				ans.push_back(make_pair(i,j));
			else{
				int nx=i+dx[dir[now]],ny=j+dy[dir[now]];
				if(nx<0||ny>=MAX_N||ny<0||ny>=MAX_N||G[nx][ny]==false)continue;
				if(vis[i][j][now][(dir[now]+1)%4]||vis[i][j][now][(dir[now]+3)%4])
					ans.push_back(make_pair(i,j));
			}
		}
	sort(ans.begin(),ans.end());
	for(int i=0;i<ans.size();i++)
		printf("%d %d\n",ans[i].first/2,ans[i].second/2);
	return 0;
}
