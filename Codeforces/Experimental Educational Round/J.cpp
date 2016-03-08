#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    long long n;
    cin>>n;
    long long tmp = 1;
    for(int i=1;i<=10;i++)
        tmp = tmp*i/__gcd(tmp,(long long)i);
    cout<<n/tmp<<endl;
}