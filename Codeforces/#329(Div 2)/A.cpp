#include<iostream>
#include<string>
#include<cstring>
#include<cstdio>
#define MAX_N 123
using namespace std;

int n;
string s[MAX_N];

int main(){
	cin.sync_with_stdio(false);
	int ans=0;
	cin>>n;
	for(int i=0;i<n;i++)cin>>s[i];
	for(char a='a';a<='z';a++)
		for(char b='a';b<='z';b++){
			int sum=0;
			for(int i=0;i<n;i++){
				bool flag=1;
				for(int j=0;j<s[i].length();j++)
					if(s[i][j]!=a&&s[i][j]!=b){
						flag=0;
						break;
					}
				if(flag)sum+=s[i].length();
			}
			ans=max(ans,sum);
		}
	cout<<ans<<endl;
	return 0;
}
