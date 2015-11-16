#include<iostream>
#include<stdio.h>
#include<unordered_map>
using namespace std;
#define maxn 100007
unordered_map<int,int> H[maxn],ans[maxn];

int fi(int x,int y)
{
    return x==H[x][y]?x:H[x][y]=fi(H[x][y],y);
}
void uni(int x,int y,int c)
{
    if(H[x].find(c)==H[x].end())H[x][c]=x;
    if(H[y].find(c)==H[y].end())H[y][c]=y;
    int p = fi(x,c),q = fi(y,c);
    if(p==q)return;
    if(p>q)swap(p,q);
    H[fi(x,c)][c]=fi(y,c);
}

int main()
{
    int n,m;scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        if(x>y)swap(x,y);
        uni(x,y,z);
    }
    int q;scanf("%d",&q);
    while(q--)
    {
        int x,y;scanf("%d%d",&x,&y);
        if(H[x].size()>H[y].size())swap(x,y);
        if(ans[x].find(y)==ans[x].end())
        {
            int Ans = 0;
            for(auto &c:H[x])
            {
                if(H[y].find(c.first)==H[y].end())continue;
                int p = fi(x,c.first),q = fi(y,c.first);
                if(p==q)Ans++;
            }
            ans[x][y] = Ans;
        }
        printf("%d\n",ans[x][y]);
    }
}
