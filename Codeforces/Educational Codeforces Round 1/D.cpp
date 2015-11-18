#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<string>
#define MAX_N 1003
using namespace std;

string G[MAX_N];
int belong[MAX_N][MAX_N];
int pic[MAX_N*MAX_N];
int dx[4]={0,1,0,-1},dy[4]={1,0,-1,0};

int n,m,q;

void dfs(int i,int j,int t){
    belong[i][j]=t;
    for(int k=0;k<4;k++){
        int nx=i+dx[k],ny=j+dy[k];
        if(nx<0||nx>=n||ny<0||ny>=m||G[nx][ny]=='*'||belong[nx][ny])continue;
        dfs(nx,ny,t);
    }
}

int main(){
    cin.sync_with_stdio(false);
    cin>>n>>m>>q;
    for(int i=0;i<n;i++)cin>>G[i];
    int tot=0;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            if(belong[i][j]==0&&G[i][j]!='*')dfs(i,j,++tot);
    //cout<<belong[1][4]<<endl;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            if(G[i][j]=='*')
                for(int k=0;k<4;k++)
                    if(i+dx[k]<n&&i+dx[k]>=0&&j+dy[k]<m&&j+dy[k]>=0&&G[i+dx[k]][j+dy[k]]!='*')
                        pic[belong[i+dx[k]][j+dy[k]]]++;
    
    while(q--){
        int x,y;
        cin>>x>>y;
        //cout<<x<<" "<<y<<endl;
        x--;y--;
//      cout<<x<<" "<<y<<" "<<belong[x][y]<<endl;
        cout<<pic[belong[x][y]]<<endl;
    }
    return 0;
}
