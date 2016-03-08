#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
int n,m,p;
void deal()
{
    int i,temp=n-m-m;
    for(i=0;(1<<i)<=temp;i++) if(temp==(1<<i))
    {
        puts("0");
        return;
    }
    for(i=1;i<20;i++) if(temp<(1<<i))
    {
        if(p>m+m+(1<<(i-1))&&p<m+m+(1<<i))
        {
            puts("Thrown");
        }
        else puts("0");
        return;
    }
}

int C;

int main()
{
    for(scanf("%d",&C);C--;)
    {
        scanf("%d%d%d",&n,&m,&p);
        if(n<=m+m)
        {
            if(n==p) printf("%d\n",m-(n-1)/2);
            else if(n%2==p%2) puts("1");
            else puts("0");
            continue;
        }
        if(n==m+m+1)
        {
            printf("%d\n",(p&1)&&p<n);
            continue;
        }
        deal();
    }
    return 0;
}