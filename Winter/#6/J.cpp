#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<vector>
#define MAX_N 15
#define MAX_M 123
using namespace std;

int n,m,k;

int a[MAX_N][MAX_M];
int b[MAX_N][MAX_M];
int c[MAX_N][MAX_M];

vector<int> v;

bool cmp(int x,int y){
	return x>y;
}

int main(){
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	cin>>n>>m>>k;
	for(int i=0;i<n;i++){
		string s;
		cin>>s;
		for(int j=0;j<m;j++)
			cin>>a[i][j]>>b[i][j]>>c[i][j];
	}
	int ans=0;
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++){
			if(i==j)continue;
			v.clear();
			for(int h=0;h<m;h++)
				for(int t=0;t<c[i][h];t++)
					if(b[j][h]-a[i][h]>0)
						v.push_back(b[j][h]-a[i][h]);
			sort(v.begin(),v.end(),cmp);
			//for(int i=0;i<v.size();i++)
			//	cout<<v[i]<<" ";
			//cout<<endl;
			int tmp=0;
			for(int h=0;h<min(k,(int)v.size());h++)
				tmp+=v[h];
			//cout<<tmp<<endl;
			ans=max(ans,tmp);
		}
	cout<<ans<<endl;
	return 0;
}