#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
#include<cstdio>
#include<queue>
#include<deque>
#include<set>
using namespace std;

int a[MAX_N];
int N;

struct BlockArray{
	int blockSize,blockNum;
	struct Block{
		set<int> se;
		deque<int> que;
		int sum,asum;
		Block(){
			se.clear();
			while(que.size())que.pop_front();
			sum=0,asum=0;
		}
	}Ar[MAX_S];
	BlockArray(){
		blockSize=sqrt(N)+1;
		blockNum=0;
		for(int i=1;i<=N;i+=blockSize){
			Ar[++blockNum]=Block();
		}
	}
	void insert(int p,int x){
		
	}
}block;

