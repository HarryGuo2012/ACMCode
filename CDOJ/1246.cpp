#include<iostream>
#include<cstring>
#include<vector>
#include<cmath>
#include<algorithm>
#include<cstdio>
#include<map>
#include<set>
#define MAX_A 100005
using namespace std;

bool isPrime[MAX_A];
vector<int> prime;

void getPrime(){
	memset(isPrime,1,sizeof(isPrime));
	for(int i=2;i<MAX_A;i++){
		if(!isPrime[i])continue;
		prime.push_back(i);
		for(int j=2*i;j<MAX_A;j+=i)isPrime[j]=0;
	}
}

int div(int x,bool &flag){
	int i=0;
	int res=0,cnt=0;
	while(i<prime.size()&&x>1){
		if(x%prime[i])i++;
		else x/=prime[i],res+=prime[i],cnt++;
	}
	if(x!=1)res+=x,cnt++;
	flag=(cnt==1);
	return res;
}

set<int> se;

map<int,int> ma;

vector<int> op;

void update(int x){
	for(int i=0;i<op.size();i++)ma[op[i]]=x;
}

int main(){
	getPrime();
	int n;
	while(scanf("%d",&n)==1){
		se.clear();
		op.clear();
		if(ma.find(n)!=ma.end()){
			printf("%d\n",ma[n]);
			continue;
		}
		if(n==1){
			printf("%d\n",n);
			continue;
		}
		op.push_back(n);
		while(true){
			bool flag;
			n=div(n,flag);
			if(ma.find(n)!=ma.end()){
				update(ma[n]);
				printf("%d\n",ma[n]);
				break;
			}
			if(flag){
				update(n);
				printf("%d\n",n);
				break;
			}
			if(se.find(n)!=se.end()){
				update(n);
				printf("-1\n");
				break;
			}
			op.push_back(n);
			se.insert(n);
		}
	}
	return 0;
}
