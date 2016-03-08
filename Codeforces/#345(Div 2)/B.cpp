#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int n;
int a[1111];

int main(){
	cin.sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++){
		int t;cin>>t;
		a[t]++;
	}
	int ans=0;
	bool flag=true;
	while(flag){
		flag=false;
		int cnt=0;
		for(int i=1;i<=1000;i++){
			if(a[i]>0)a[i]--,cnt++;
		}
		if(cnt>1)flag=true;
		else break;
		ans+=cnt-1;
	}
	cout<<ans<<endl;//cin>>n;
	return 0;
}