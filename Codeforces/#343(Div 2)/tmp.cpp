#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 110
using namespace std;
typedef long long ll;
int sr,sb,sg,n,m,mod;
int cir[N][N],v[N],size[N];
ll f[N][N][N],ans;
int calc(int x)
{
    int cnt=0;
    memset(v,0,sizeof(v));
    memset(size,0,sizeof(size));
    for(int i=1;i<=n;i++)
    {
        if(v[i])continue;
        int p=cir[x][i];
        cnt++;
        while(!v[p])v[p]=1,size[cnt]++,p=cir[x][p];
    }
    cout<<cnt<<endl;
    memset(f,0,sizeof(f));
    f[0][0][0]=1;
    for(int i=1;i<=cnt;i++)
        for(int j=sr;j>=0;j--)
            for(int k=sb;k>=0;k--)
                for(int l=sg;l>=0;l--)
                {
                    if(j>=size[i])f[j][k][l]=(f[j][k][l]+f[j-size[i]][k][l])%mod;
                    if(k>=size[i])f[j][k][l]=(f[j][k][l]+f[j][k-size[i]][l])%mod;
                    if(l>=size[i])f[j][k][l]=(f[j][k][l]+f[j][k][l-size[i]])%mod;
                }
    return f[sr][sb][sg];
}
ll quick_my(ll x,int y)
{
    ll ret=1;
    while(y)
    {
        if(y&1)ret=(ret*x)%mod;
        x=(x*x)%mod;
        y>>=1;
    }
    return ret;
}
int main()
{
    scanf("%d%d%d%d%d",&sr,&sb,&sg,&m,&mod);
    n=sr+sb+sg;
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
            scanf("%d",&cir[i][j]);
    m++;
    for(int i=1;i<=n;i++)cir[m][i]=i;
    ll ans=0;
    for(int i=1;i<=m;i++)ans=(ans+calc(i))%mod;
    ans=(ans*quick_my(m,mod-2))%mod;
    printf("%lld\n",ans);
    scanf("%d",&n);
}