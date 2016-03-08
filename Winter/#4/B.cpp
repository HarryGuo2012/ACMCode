//#include<iostream>
#include<cstring>
#include<algorithm>
#include<fstream>
#include<climits>
#define INF LLONG_MAX
using namespace std;

long long sum[2000];
int cnt[2000];

int Get(int x){
	int res=0;
	while(x){
		res+=x%10;
		x/=10;
	}
	return res;
}

int main(){
	ifstream cin("digits.in");
	ofstream cout("digits.out");
	int n;
	cin>>n;
	for(int i=1;i<=100000;i++){
		int t=Get(i);
		if(cnt[t]==n)continue;
		sum[t]=sum[t]+i;
		cnt[t]++;
	}
	long long ans=INF;
	for(int i=1;i<2000;i++)
		if(cnt[i]==n)
			ans=min(ans,sum[i]);
	cout<<ans<<endl;
	return 0;
}
