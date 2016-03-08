#include<bits/stdc++.h>
using namespace std;

int cal(int x)
{
    map<int,int> H;
    for(int i=2;i<=x;i++)
    {
        while(x%i==0)
        {
            x/=i;
            H[i]++;
        }
    }
    long long ans = 1;
    map<int,int>::iterator it;
    for(it = H.begin();it!=H.end();it++)
        ans = ans * (it->second+1);
    return ans;
}
int main()
{
    freopen("1.out","w",stdout);
    int n;n=10000000;
    int m1=0,m2=0;
    int cnt = 1;
    int d;int pre=0;
    for(int i=1;i<=n;i++)
    {
        if(i>100&&i%2==1)continue;
        if(i>10000&&i%20!=0)continue;
        d = cal(i);
        if(d>=m1)
        {
            m2 = m1;
            m1 = d;
            printf("%d %d %d\n",cnt++,i,i-pre);
            pre=i;
            if(i>10000)i+=200;
            if(i>128520)i+=2000;
        }
        else if(m2<=d)
        {
            m2 = d;
            printf("%d %d %d\n",cnt++,i,i-pre);
            pre=i;
            if(i>10000)i+=200;
            if(i>128520)i+=2000;
        }
    }
}
