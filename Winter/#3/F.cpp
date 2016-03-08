#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
#include<cstdio>
#define MAX_N 15
#define INF 12345678
using namespace std;

bool G[MAX_N][MAX_N];
int H[MAX_N][MAX_N];
int n,m;
struct piece{
	int x,y;
	char ty;
	piece(int xx,int yy,char cc):x(xx),y(yy),ty(cc){}
	piece(){}
}P[MAX_N];
int tot=0;

int kx[8]={2,2,-2,-2,1,1,-1,-1},ky[8]={1,-1,1,-1,2,-2,2,-2};
int rx[4]={0,1,0,-1},ry[4]={1,0,-1,0};
int bx[4]={1,1,-1,-1},by[4]={1,-1,1,-1};

void draw(int s){
	memset(G,0,sizeof(G));
	memset(H,-1,sizeof(H));
	for(int i=0;i<tot;i++)
		if((s>>i)&1)
			H[P[i].x][P[i].y]=i;
	for(int i=0;i<tot;i++)
		if((s>>i)&1){
			switch(P[i].ty){
				case 'K':
					for(int k=0;k<8;k++){
						int nx=kx[k]+P[i].x,ny=ky[k]+P[i].y;
						if(nx<0||nx>=n||ny<0||ny>=m)continue;
						G[nx][ny]=1;
					}
					break;
				case 'R':
					for(int k=0;k<4;k++){
						for(int t=1;;t++){
							int nx=t*rx[k]+P[i].x,ny=t*ry[k]+P[i].y;
							if(nx<0||nx>=n||ny<0||ny>=m)break;
							G[nx][ny]=1;
							if(H[nx][ny]!=-1)break;
						}
					}
					break;
				case 'B':
					for(int k=0;k<4;k++){
						for(int t=1;;t++){
							int nx=t*bx[k]+P[i].x,ny=t*by[k]+P[i].y;
							if(nx<0||nx>=n||ny<0||ny>=m)break;
							G[nx][ny]=1;
							if(H[nx][ny]!=-1)break;
						}
					}
					break;
			}
		}
}

int dp[MAX_N][MAX_N][1<<MAX_N];

void output(bool v[MAX_N][MAX_N]){
	for(int i=0;i<n;i++,cout<<endl)
		for(int j=0;j<m;j++)
			cout<<v[i][j]<<" ";
	cout<<"-----"<<endl;
}
char cc;
void dfs(int i,int j,int s){
	for(int k=0;k<4;k++){
		draw(s);
		int t=s;
		int nx=rx[k]+i,ny=ry[k]+j;
		if(nx<0||nx>=n||ny<0||ny>=m||G[nx][ny])continue;
		if(H[nx][ny]!=-1){
			int tmp=(1<<tot)-1-(1<<H[nx][ny]);
			t=s&tmp;
		}
		if(dp[nx][ny][t]>dp[i][j][s]+1){
			dp[nx][ny][t]=dp[i][j][s]+1;
			dfs(nx,ny,t);
		}
	}
	for(int k=0;k<4;k++){
		draw(s);
		int t=s;
		int nx=bx[k]+i,ny=by[k]+j;
		if(nx<0||nx>=n||ny<0||ny>=m||G[nx][ny])continue;
		if(H[nx][ny]!=-1){
			int tmp=(1<<tot)-1-(1<<H[nx][ny]);
			t=s&tmp;
		}
		if(dp[nx][ny][t]>dp[i][j][s]+1){
			dp[nx][ny][t]=dp[i][j][s]+1;
			dfs(nx,ny,t);
		}
	}
}

int sx,sy;

int main(){
	cin>>n>>m;
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++){
			char g;
			cin>>g;
			if(g=='*')
				sx=i,sy=j;
			else if(g!='.')
				P[tot++]=piece(i,j,g);
		}
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			for(int k=0;k<(1<<tot);k++)
				dp[i][j][k]=INF;
	dp[sx][sy][(1<<tot)-1]=0;
	dfs(sx,sy,(1<<tot)-1);
	int ans=INF;
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			ans=min(ans,dp[i][j][0]);
	if(ans==INF)
		cout<<-1<<endl;
	else
		cout<<ans<<endl;
	return 0;
}
