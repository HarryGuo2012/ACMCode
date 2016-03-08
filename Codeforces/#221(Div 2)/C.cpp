#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

int a[4]={1,6,8,9};
string s;

int cnt[10];

int main(){
	cin.sync_with_stdio(false);
	cin>>s;
	for(int i=0;i<s.length();i++)
		cnt[s[i]-'0']++;
	cnt[1]--,cnt[6]--,cnt[8]--,cnt[9]--;
	bool flag=false;
	int now=0;
	for(int i=9;i>0;i--){
		while(cnt[i]){
			cout<<i;
			now=now*10+i;
			now%=7;
			cnt[i]--;
			flag=true;
		}
	}
	if(!flag){
		cout<<"1869";
		for(int i=0;i<cnt[0];i++)
			cout<<0;
		cout<<endl;
		return 0;
	}
	now=now*10000%7;
	do{
		int b=0;
		for(int i=0;i<4;i++)
			b=b*10+a[i];
		if((b+now)%7==0){
			for(int i=0;i<4;i++)
				cout<<a[i];
			for(int i=0;i<cnt[0];i++)
				cout<<0;
			cout<<endl;
			return 0;
		}
	}while(next_permutation(a,a+4));
	cout<<0<<endl;
	return 0;
}
