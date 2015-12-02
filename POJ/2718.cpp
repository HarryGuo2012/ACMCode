#include<iostream>
#include<algorithm>
#include<cstdio>
#include<climits>
#include<cmath>
using namespace std;

int T;
string s;

vector<int> a;

int main(){
	cin.sync_with_stdio(false);
	cin>>T;
	getline(cin,s);
	while(T--){
		getline(cin,s);
		for(int i=0;i<s.length();i+=2)a.push_back(s[i]-'0');
		int n=a.size();
		int ans=INT_MAX;
		for(int i=1;i<(1<<n)-2;i++){
			vector<int> x,y;
			for(int j=0;j<n;j++){
				if((1<<j)&i)x.push_back(a[i]);
				else y.push_back(a[i]);
			}
			do{
				if(x[0]==0&&x.size()>1)continue;
				int xx=0;
				for(int j=x.size()-1;j>=0;j--)xx=xx*10+x[j];
				do{
					if(y[0]==0&&y.size()>1)continue;
					int yy=0;
					for(int j=y.size()-1;j>=0;j--)yy=yy*10+y[j];
					ans=min(ans,abs(xx-yy));
				}while(next_permutation(y.begin(),y.end()));
			}while(next_permutation(x.begin(),x.end()));
		}
		cout<<ans<<endl;
	}
	return 0;
}
