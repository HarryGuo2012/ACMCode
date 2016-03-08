#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

typedef long long ll;

class Bitset{
public:
	vector<ll> v;
	int len;
	Bitset(int x){
		len=x;
		v.resize(x/60+5,0);
	}
	void clear(){
		v.clear();
	}
	Bitset operator=(vector<ll> vv):v(vv){}
	bool operator<(Bitset b){
		if(v.size()<b.v.size())return true;
		if(v.size()>b.v.size())return false;
		
		for(int i=v.size()-1;i>=0;i--){
			if(v[i]==b.v[i])continue;
			if(v[i]>b.v[i])return false;
			if(v[i]<b.v[i])return true;
		}
	}
	bool operator>(Bitset b){
		return b<*this;
	}
	bool operator!=(Bitset b){
		return *this<b||*this>b;
	}
	bool operator==(Bitset b){
		return !(*this!=b);
	} 
	Bitset operator&(Bitset b){
		Bitset res(len);
		for(int i=0;i<v.size();i++)
			res.v[i]=v[i]&b.v[i];
		return res;
	}
	Bitset operator|(Bitset b){
		Bitset res(len);
		for(int i=0;i<v.size();i++)
			res.v[i]=v[i]|b.v[i];
	}
	Bitset operator^(Bitset b){
		Bitset res(len);
		for(int i=0;i<v.size();i++)
			res.v[i]=v[i]^b.v[i];
	}
	Bitset operator<<(int x){
		Bitset res(len);
		int a=x/60,b=x%60;
		int c=60-b;
		for(int i=0;i<v.size();i++){
			int f=(i-a<0)?0:v[i-a],g=(i-a-1<0)?0:v[i-a-1];
			res.v[i]=(f<<b)|(g>>c);
		}
		return  res;
	}
	Bitset operator>>(int x){
		Bitset res(len);
		int a=x/60,b=x%60;
		int c=60-b;
		for(int i=0;i<v.size();i++){
			int f(i+a>=v.size())0:v[i+a],g=(i+a+1>=v.size())?0:v[i+a+1];
			res.v[i]=(f>>b)|(g<<c);
		}
		return res;
	}
	vector<int> allOne(){
		vector<int> ones;
		ones.clear();
		for(int i=0;i<v.size();i++)
			ones.push_back(__builtin_ffs(v[i])+i*60);
		return ones;
	}
	int count(){
		int res=0;
		for(int i=0;i<v.size();i++)
			res+=__builtin_popcount(v[i]);
		return res;
	}
};