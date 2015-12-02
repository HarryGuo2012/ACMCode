#include<iostream>
#include<cstring>
#include<string>
#include<vector>
#include<algorithm>
#define MAX_N 100005
using namespace std;
int n;
string s;

vector<char> v;

int main(){
	cin.sync_with_stdio(false);
	cin>>n>>s;
	if(n==1||n==2||n==3){
		cout<<n<<endl;
		return 0;
	}
	bool flag=true;
	v.push_back(s[0]);
	for(int i=1;i<n;i++){
		if(s[i]==s[i-1]){
			flag=false;
			continue;
		}
		v.push_back(s[i]);
	}
	int cnt=v.size();
	if(flag)cout<<cnt<<endl;
	else cout<<min(cnt+2,n)<<endl;
	return 0;
}
