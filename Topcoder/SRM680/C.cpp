#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#define MAX_N 55
using namespace std;

bool dp[MAX_N][MAX_N][MAX_N];

int get0(int L,int R){
	return R/3-(L-1)/3;
}

int g1(int n){
	if(n%3!=0)return n/3+1;
	return n/3;
}

int get1(int L,int R){
	return g1(R)-g1(L-1);
}

int g2(int n){
	if(n%3==2)return n/3+1;
	return n/3;
}

int get2(int L,int R){
	return g2(R)-g2(L-1);
}

int up[MAX_N],qu[MAX_N],sum[MAX_N];
int m;

struct node{
	int u,q;
	node(int uu,int qq):u(uu),q(qq){}
	node();
};

bool cmp(node x,node y){
	return x.u<y.u;
}

vector<node> allNode;

class BearFair2{
public:
	string isFair(int n, int b, vector <int> upTo, vector <int> quantity){
		memset(dp,0,sizeof(dp));
		m=upTo.size();
		for(int i=0;i<m;i++)
			allNode.push_back(node(upTo[i],quantity[i]));
		sort(allNode.begin(),allNode.end(),cmp);
		for(int i=1;i<=m;i++){
			up[i]=allNode[i-1].u;
			qu[i]=allNode[i-1].q;
			sum[i]=sum[i-1]+qu[i];
		}
		m++;
		up[m]=b;
		qu[m]=n-sum[m-1];
		sum[m]=n;
		for(int i=1;i<=m;i++)
			if(qu[i]<qu[i-1])
				return "unfair";
		dp[0][0][0]=1;
		for(int i=1;i<=m;i++)
			for(int j=0;j<=n/3;j++)
				for(int k=0;k<=n/3;k++)
					for(int x=0;x<=j;x++)
						for(int y=0;y<=k;y++){
							int l=sum[i]-j-k,z=sum[i-1]-x-y;
							if(l<0||z<0||l<z||dp[i-1][x][y]==0)continue;
							int a0=l-z,a1=j-x,a2=k-y;
							int L=up[i-1]+1,R=up[i];
							if(get0(L,R)>=a0&&get1(L,R)>=a1&&get2(L,R)>=a2)
								dp[i][j][k]=1;
						}
		if(dp[m][n/3][n/3])return "fair";
		else return "unfair";
	}
};

int main(){
	return 0;
}