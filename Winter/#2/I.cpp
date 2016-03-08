#include<string>
#include<cmath>
#include<vector>
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<stack>
using namespace std;

const long double eps=1e-8;

int n;

stack<long double> st;

vector<string> vs;

long double GetXiper(long double xiper){
	while(st.size())st.pop();
	for(int i=0;i<n;i++){
		string s=vs[i];
		if(s[0]=='x')st.push(xiper);
		if(s[0]=='s'){
			long double now=st.top();
			st.pop();
			st.push(sin(now));
		}
		if(s[0]=='c'){
			long double now=st.top();
			st.pop();
			st.push(cos(now));
		}
		if(s[0]=='t'){
			long double now=st.top();
			st.pop();
			st.push(tan(now));
		}
		if(s[0]=='+'){
			long double u=st.top();st.pop();
			long double v=st.top();st.pop();
			st.push(v+u);
		}
		if(s[0]=='-'){
			long double u=st.top();st.pop();
			long double v=st.top();st.pop();
			st.push(v-u);
		}
		if(s[0]=='*'){
			long double u=st.top();st.pop();
			long double v=st.top();st.pop();
			st.push(v*u);
		}
	}
	long double now=st.top();st.pop();
	return now;
}

int main(){
//	cin.sync_with_stdio(false);
	while(true){
		cin>>n;
		if(n==0)break;
		vs.clear();
		for(int i=0;i<n;i++){
			string s;
			cin>>s;
			vs.push_back(s);
		}
		bool flag;
		if(fabs(GetXiper(538)*GetXiper(-0.048))<eps
			&&fabs(GetXiper(9876)-GetXiper(-1.23))<eps
			&&fabs(GetXiper(244)+GetXiper(1.89))<eps
			&&fabs(GetXiper(0.12))<eps)
			flag=true;
		else
			flag=false;
		if(flag)
			cout<<"Identity"<<endl;
		else
			cout<<"Not an identity"<<endl;
	}
	return 0;
}

