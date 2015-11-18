#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
#include<string>
#include<queue>
#include<climits>
#define INF INT_MAX
#define MAX_N 55
using namespace std;

int dp[MAX_N][MAX_N][MAX_N];

int main(){
    for(int i=1;i<=30;i++)
        for(int j=1;j<=30;j++){
            for(int k=0;k<MAX_N;k++)
                dp[i][j][k]=INF;
            if(i*j<=50)dp[i][j][i*j]=0;
        }
    for(int i=1;i<=30;i++)
        for(int j=1;j<=30;j++){
            for(int a=1;a<i;a++)
                for(int x=1;x<=min(50,a*j);x++)
                    for(int y=1;y<=min(50,(i-a)*j);y++){
                        dp[i][j][x]=min(dp[i][j][x],dp[a][j][x]+j*j);
                        dp[i][j][y]=min(dp[i][j][y],dp[i-a][j][y]+j*j);
                        if(x+y>50)continue;
                        dp[i][j][x+y]=min(dp[i][j][x+y],dp[a][j][x]+dp[i-a][j][y]+j*j);
                    }
            for(int b=1;b<j;b++)
                for(int x=1;x<=min(50,b*i);x++)
                    for(int y=1;y<=min(50,(j-b)*i);y++){
                        dp[i][j][x]=min(dp[i][j][x],dp[i][b][x]+i*i);
                        dp[i][j][y]=min(dp[i][j][y],dp[i][j-b][y]+i*i);
                        if(x+y>50)continue;
                        dp[i][j][x+y]=min(dp[i][j][x+y],dp[i][b][x]+dp[i][j-b][y]+i*i);
                    }
        }
    int q;
    cin.sync_with_stdio(false);
    cin>>q;
    while(q--){
        int i,j,k;
        cin>>i>>j>>k;
        cout<<dp[i][j][k]<<endl;
    }
    return 0;
}
