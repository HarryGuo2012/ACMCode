#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <cstring>
#include <cstdio>

using namespace std;

struct node
{
    long long x;
    int id;
    int a;
    int b;
}num[100000],ans[100000];

int n,m,cnt,tree[100100],lcnt,l,r,mid;
long long sum,nn,calnum[100100],mm,mc;
map <long long,int>cal;
vector <int> idnum[100100];

bool cmp1(node A,node B)
{
    return A.x<B.x;
}

bool cmp2(node A,node B)
{
    return A.id<B.id;
}

void add(int k,int num)
{
    while(k<=n)
    {
        tree[k]+=num;
        k+=k&-k;
    }
}
int read(int k)
{
    int ssum=0;
    while(k)
    {
        ssum+=tree[k];
        k-=k&-k;
    }
    return ssum;
}


int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++)
    {
        scanf("%lld",&num[i].x);
        num[i].id=i+1;
    }
    for(int i=0;i<m;i++)
    {
        scanf("%lld",&ans[i].x);
        ans[i].id=i+1;
    }
    sort(num,num+n,cmp1);
    sort(ans,ans+m,cmp1);
    for(int i=0;i<n;i++)
    {
        if(!cal[num[i].x])cal[num[i].x]=++cnt;
        calnum[cnt]=num[i].x;
        idnum[cnt].push_back(num[i].id);
    }
    for(int i=1;i<=n;i++)add(i,1);
    sum=0;nn=n;lcnt=1;
    for(int i=0;i<m;i++)
    {
        if(ans[i].x<=sum+nn*(calnum[lcnt]-calnum[lcnt-1]))
        {
            mm=(ans[i].x-sum)%nn;if(mm==0)mm=nn;
            mc=(ans[i].x-sum-1)/nn;
            l=1;r=n;
            while(l!=r)
            {
                mid=((l+r)>>1);
                if(read(mid)>=mm)r=mid;
                else l=mid+1;
            }
            ans[i].a=l;
            ans[i].b=calnum[lcnt-1]+mc+1;
        }
        else
        {
            sum+=nn*(calnum[lcnt]-calnum[lcnt-1]);
            for(int j=0;j<idnum[lcnt].size();j++)add(idnum[lcnt][j],-1);
            nn-=idnum[lcnt].size();
            lcnt++;
            i--;
        }
    }
    sort(ans,ans+m,cmp2);
    for(int i=0;i<m;i++)printf("%d %d\n",ans[i].a,ans[i].b);
    return 0;
}