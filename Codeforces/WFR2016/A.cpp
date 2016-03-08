#include<iostream>
#include<cstring>
#include<stack>
#include<algorithm>
#include<vector>
using namespace std;

stack<int> st;
vector<int> v;

int n;

int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		st.push(1);
		while(st.size()>1){
			int u=st.top();st.pop();
			int v=st.top();st.pop();
			if(u==v)st.push(u+1);
			else{
				st.push(v);st.push(u);
				break;
			}
		}
	}
	while(st.size()){
		v.push_back(st.top());st.pop();
	}
	for(int i=v.size()-1;i>=0;i--)cout<<v[i]<<" ";
	cout<<endl;
	return 0;
}