#include<iostream>
#include<cstring>
#include<vector>
#include<string>
#include<algorithm>
#define MAX_N 123
using namespace std;

bool vis[MAX_N][MAX_N][MAX_N];
bool dp[MAX_N][MAX_N][MAX_N];

vector<string> G;
int R,C;
int dx[4]={1,0,-1,0},dy[4]={0,1,0,-1};
int ex,ey;

int K;

void init(){
	for(int i=0;i<R;i++)
		for(int j=0;j<C;j++){
			vis[i][j][0]=1;
			dp[i][j][0]=0;
		}	
	for(int i=0;i<=K;i++){
		vis[ex][ey][i]=1;
		dp[ex][ey][i]=0;
	}
}

bool dfs(int x,int y,int z){
	if(vis[x][y][z])return dp[x][y][z];
	bool res=1;
	for(int i=0;i<4;i++){
		int nx=x+dx[i],ny=y+dy[i];
		if(nx>=R||ny>=C||nx<0||ny<0||G[nx][ny]=='#')continue;
		res&=dfs(nx,ny,z-1);
	}
	dp[x][y][z]=!res;
	vis[x][y][z]=1;
	return dp[x][y][z];
}

int tx,ty;

class BoardEscapeDiv2{
	public:
		string findWinner(vector <string> s, int k){
			G=s;
			K=k;
			R=s.size();
			C=s[0].length();
			for(int i=0;i<R;i++)
				for(int j=0;j<C;j++){
					if(G[i][j]=='T')tx=i,ty=j;
					if(G[i][j]=='E')ex=i,ey=j;
				}
			if(dfs(tx,ty,K))return "Alice";
			else return "Bob";
		}	
};

