#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#define MAX_N 222
using namespace std;

struct Matrix{
	vector<int> G[MAX_N];
	int n,m;
	Matrix(){
		for(int i=0;i<MAX_N;i++)G[i].resize(MAX_N,0);
	}
	Matrix operator=(Matrix a){
		n=a.n,m=a.m;
		for(int i=0;i<MAX_N;i++)G[i][j]=a.G[i][j];
	}
	Matrix operator*(Matrix a){
		Matrix res;
		res.n=n,res.m=a.m;
		for(int i=0;i<n;i++)
			for(int j=0;j<a.m;j++){
				long long tmp=0;
				for(int k=0;k<m;k++)
					tmp+=G[i][k]*a.G[k][j]%mod;
			}
		return res;
	}
	Matrix Pow(long long n){
		Matrix a=*this,res;
		while(n){
			if(n&1)res=res*a;
			a=a*a;
			n>>=1;
		}
		return res;
	}
};

int main(){
	return 0;
}