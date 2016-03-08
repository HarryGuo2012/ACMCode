#include<iostream>
#include<set>
#include<vector>
#include<algorithm>
#include<cstdio>
#define MAX_N 100005
using namespace std;

struct node{
    int a,b,id;
    friend bool operator<(const node &x,const node &y){
        return x.a<y.a;
    }
    node(int aa,int bb,int ii):a(aa),b(bb),id(ii){}
    node(){}
};

int dp[MAX_N];

node bea[MAX_N];
set<node> se;
int n;

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        int a,b;
        scanf("%d%d",&a,&b);
        bea[i]=node(a,b,i);
    }
    sort(bea+1,bea+1+n);
    for(int i=1;i<=n;i++){
        auto it=se.lower_bound(node(bea[i].a-bea[i].b,0,0));
        if(se.empty()||it==se.begin())dp[bea[i].id]=1;
        else{
            it--;
            dp[bea[i].id]=dp[it->id]+1;
        }
        se.insert(bea[i]);
    }
    int ans=0;
    for(int i=1;i<=n;i++)
        ans=max(ans,dp[i]);
    cout<<n-ans<<endl;
    return 0;
}
