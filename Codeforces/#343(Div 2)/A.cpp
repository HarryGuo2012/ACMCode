#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
using namespace std;

typedef long long ll;
string s[111];

int n;
ll ans=0;

int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		cin>>s[i];
	for(int i=0;i<n;i++){
		ll cnt1=0,cnt2=0;
		for(int j=0;j<n;j++){
			if(s[i][j]=='C')cnt1++;
			if(s[j][i]=='C')cnt2++;
		}
		ans+=cnt1*(cnt1-1)/2+cnt2*(cnt2-1)/2;
	}
	cout<<ans<<endl;
	//cin>>n;
	return 0;
}