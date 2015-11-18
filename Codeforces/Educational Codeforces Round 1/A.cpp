#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

typedef long long ll;

ll n;
int T;

int main(){
    cin.sync_with_stdio(false);
    cin>>T;
    while(T--){
        cin>>n;
        ll k=1;
        while(k<=n)k*=2;
        cout<<(1+n)*n/2-k+1-k+1<<endl;
    }
    return 0;
}
