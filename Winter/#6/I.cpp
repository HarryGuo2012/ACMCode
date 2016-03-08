#include<iostream>
#include<string>
#include<vector>
#include<cstring>
#include<cstdio>
#include<algorithm>
#define MAX_N 100005
using namespace std;

string s,t;
typedef long long ll;

ll k;
ll n;
string u,v,tmp;
int check(){
	int res=0;
	for(int i=1;i<n;i++){
		u.assign(s.begin(),s.begin()+i);
		v.assign(s.begin()+i,s.end());
		tmp=v+u;
		if(tmp==t)res++;
	}
	return res;
}

ll mod=1000000007;

ll Pow(ll a,ll x){
	ll res=1;
	while(x){
		if(x&1)res*=a;
		x>>=1;
		a=a*a%mod;
		res%=mod;
	}
	return res%mod;
}

ll f[MAX_N];

int main(){
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	cin>>s>>t>>k;
	n=s.length();
	if(s.length()!=t.length()){
		cout<<0<<endl;
		return 0;
	}
	n=s.length();
	if(k==0){
		if(s!=t)cout<<0<<endl;
		else cout<<1<<endl;
		return 0;
	}
	int cnt=check();
	if(k==1){
		cout<<cnt<<endl;
		return 0;
	}
	if(s!=t&&cnt==0){
		cout<<0<<endl;
		return 0;
	}
	t=s;
	cnt=check()-1;
	for(int i=2;i<MAX_N;i++)
		f[i]=(-f[i-1]+Pow(i-1,k-1))%mod;
	cout<<f[n]*cnt<<endl;
	return 0;
}