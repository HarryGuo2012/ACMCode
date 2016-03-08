#include <iostream>
using namespace std;

long long n,ans;

int main()
{ 
    cin>>n;
    for(int i=5;i<=7;i++)
    {
        long long tmp = 1;
        for(int j=1;j<=i;j++)
            tmp=tmp*(n-j+1)/j;
        ans+=tmp;
    }
    cout<<ans<<endl;
    return 0;
}