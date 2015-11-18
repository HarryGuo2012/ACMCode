#include<iostream>
#include<cstring>
#include<vector>
#include<string>
#define MAX_N 10004
using namespace std;

string s;

int a[MAX_N];
int ans[MAX_N];
int main(){
    cin.sync_with_stdio(false);
    cin>>s;
    for(int i=0;i<s.length();i++)a[i]=i;
    int n;
    cin>>n;
    while(n--){
        int l,r,k;
        cin>>l>>r>>k;
        l--,r--;
        int mod=r-l+1;
        for(int i=0;i<s.length();i++)
            if(l<=a[i]&&a[i]<=r)a[i]=(a[i]-l+k)%mod+l;
    }
    for(int i=0;i<s.length();i++)ans[a[i]]=i;
    for(int i=0;i<s.length();i++)cout<<s[ans[i]];
    cout<<endl;
    return 0;
}
