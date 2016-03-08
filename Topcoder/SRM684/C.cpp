#include <iostream>
#include <cstring>
#include <vector>
#include <cstdio>
#include <set>
#include <algorithm>
#include <queue>
#include <stack>
#define MAX_N 55
using namespace std;

vector<int> G[MAX_N];
stack<int> st;
int dfn[MAX_N],low[MAX_N],ind=0;
bool inStack[MAX_N],vis[MAX_N];
int tot=0,id[MAX_N];

void Tarjan(int u) {
    dfn[u] = low[u] = ++ind;
    st.push(u);
    inStack[u] = 1;
    vis[u] = 1;
    for (int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        if (!vis[v]) {
            Tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if (inStack[v])
            low[u] = min(low[u], dfn[v]);
    }
    if (low[u] == dfn[u]) {
        tot++;
        int t;
        do {
            t = st.top();
            st.pop();
            inStack[t] = 0;
            id[t] = tot;
        } while (t != u);
    }
}

int cnt=0;

vector<int> newG[MAX_N];
int dp[MAX_N];

void dfs2(int u,int p){
	dp[u]=max(dp[u],dp[p]+1);
	cnt=max(cnt,dp[u]);
	for(int i=0;i<newG[u].size();i++){
		int v=newG[u][i];
		if(v==p)continue;
		dfs2(v,u);
	}
}
set<int> se;
class Autohamil{
public:
	string check(vector<int> z0,vector<int> z1){
		int n=z0.size();
		for(int i=0;i<z0.size();i++)
			G[i].push_back(z0[i]);
		for(int i=0;i<z1.size();i++)
			G[i].push_back(z1[i]);
		memset(vis,0,sizeof(vis));
		Tarjan(0);
		for(int i=0;i<n;i++)
			if(!vis[i])return "Does not exist";
		for (int u = 0; u < n; u++)
            for (int i = 0; i < G[u].size(); i++)
                if (id[u] != id[G[u][i]]){
                	//cout<<id[u]<<" "<<id[G[u][i]]<<endl;
                    newG[id[u]].push_back(id[G[u][i]]);
                }
        for(int u=0;u<n;u++)
        	se.insert(id[u]);
        cnt=0;
        dfs2(id[0],0);
        //cout<<cnt<<endl;
        if(cnt==se.size())return "Exists";
        else return "Does not exist";
	}
};

int main(){
	Autohamil f;
	vector<int> z0,z1;
	z0.push_back(1);z0.push_back(1);
	z1.push_back(1);z1.push_back(1);
	cout<<f.check(z0,z1)<<endl;int a;cin>>a;
}