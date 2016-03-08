#include<iostream>
#include<cstring>
#include<vector>
#include<string>
#include<algorithm>
#define MAX_N 200005
using namespace std;

typedef long long ll;

string a,b;
ll sum[MAX_N][2];

int A[MAX_N],B[MAX_N];

int main(){
    cin.sync_with_stdio(false);
    cin>>a>>b;
    int n=a.length(),m=b.length();
    for(int i=1;i<=n;i++)
        A[i]=a[i-1]-'0';
    for(int i=1;i<=m;i++)
        B[i]=b[i-1]-'0';
    for(int i=1;i<=m;i++)
        sum[i][B[i]]=sum[i-1][B[i]]+1,sum[i][!B[i]]=sum[i-1][!B[i]];
    ll ans=0;
    for(int i=1;i<=n;i++)
        ans+=sum[m-n+i][!A[i]]-sum[i-1][!A[i]];
    cout<<ans<<endl;
    return 0;
}
