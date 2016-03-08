#include <iostream>
#include <string>
using namespace std;

typedef long long ll;
ll n,p,now,ans;
string s[1234];

int main(){
    cin>>n>>p;
    for(int i=0;i<n;i++)cin>>s[i];
    for(int i=n-1;i>=0;i--){
        if(s[i].size()==4)
            ans+=now*p,now<<=1;
        else
            ans+=(p>>1)+now*p,now=(now<<1)+1;
    }
    cout<<ans<<endl;
    return 0;
}

