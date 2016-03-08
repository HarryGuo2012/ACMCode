#include<string>
#include<cmath>
#include<vector>
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<stack>
using namespace std;

const double xiper=23.1246597;
const double eps=1e-8;

int n;

stack<double> st;

int mai(){
	cin.sync_with_stdio(false);
	while(true){
		cin>>n;
		if(n==0)break;
		while(st.size())st.pop();
		for(int i=0;i<n;i++){
			string s;
			cin>>s;
			if(s[0]=='x')st.push(xiper);
			if(s[0]=='s'){
				double now=st.top();
				st.pop();
				st.push(sin(now));
			}
			if(s[0]=='c'){
				double now=st.top();
				st.pop();
				st.push(cos(now));
			}
			if(s[0]=='t'){
				double now=st.top();
				st.pop();
				st.push(tan(now));
			}
			if(s[0]=='+'){
				double u=st.top();st.pop();
				double v=st.top();st.pop();
				st.push(v+u);
			}
			if(s[0]=='-'){
				double u=st.top();st.pop();
				double v=st.top();st.pop();
				st.push(v-u);
			}
			if(s[0]=='*'){
				double u=st.top();st.pop();
				double v=st.top();st.pop();
				st.push(v*u);
			}
		}
		double now=st.top();st.pop();
		if(fabs(now)<eps)
			cout<<"Identity"<<endl;
		else
			cout<<"Not an identity"<<endl;
	}
	return 0;
}


