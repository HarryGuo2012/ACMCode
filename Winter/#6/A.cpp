#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
#include<string>
#include<cstdio>
using namespace std;

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

string a;
string b;

long long n;

int lcm(int x,int y){
	return x*y/gcd(x,y);
}

int qsc,xiper;

int tq,tx;

int main(){
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	//cout<<gcd(3,7)<<endl;
	cin>>n>>a>>b;
	int m=a.length(),k=b.length();
	int t=lcm(m,k);
	for(int i=0;i<t;i++){
		char u=a[i%m],v=b[i%k];
		if(u=='R'){
			if(v=='P')qsc++;
			if(v=='S')xiper++;
		}
		if(u=='P'){
			if(v=='R')xiper++;
			if(v=='S')qsc++;
		}
		if(u=='S'){
			if(v=='R')qsc++;
			if(v=='P')xiper++;
		}
	}
	for(int i=0;i<n%t;i++){
		char u=a[i%m],v=b[i%k];
		if(u=='R'){
			if(v=='P')tq++;
			if(v=='S')tx++;
		}
		if(u=='P'){
			if(v=='R')tx++;
			if(v=='S')tq++;
		}
		if(u=='S'){
			if(v=='R')tq++;
			if(v=='P')tx++;
		}
	}
	cout<<(n/t)*qsc+tq<<" "<<(n/t)*xiper+tx<<endl;
	return 0;
}