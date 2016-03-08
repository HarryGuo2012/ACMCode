#include<bits/stdc++.h>
using namespace std;
int n,m;
int check(long long k)
{
    if(k<=30&&n>(1<<k))return 0;
    long long t = 1LL*k*m;
    long long N = n;
    long long C = 1;
    long long ans = 0;
    for(int i=0;N>0;i++)
    {
        long long p = min(C,N);
        N-=p;
        ans+=p*i;
        C = C*(k-i)/(i+1);
        //cout<<i<<" "<<N<<" "<<p<<endl;
    }
    return ans<=t?1:0;
}
int main()
{
    int t;scanf("%d",&t);
    while(t--){
    scanf("%d%d",&n,&m);
    int l = 0,r = n;
    int ans = 0;
    while(l<=r)
    {
        int mid = (l+r)/2;
        if(check(mid))r=mid-1,ans=mid;
        else l=mid+1;
    }
    cout<<ans<<endl;
    }
}