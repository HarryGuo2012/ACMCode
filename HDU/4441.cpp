#include<iostream>
#include<deque>
#include<cstring>
#include<algorithm>
#include<set>
#include<queue>
#include<vector>
#include<functional>
#define MAX_N 100005
#define MAX_QN 1003
using namespace std;

struct node{
	deque<int> que;
	set<int> se;
	int sum;
	node(){
		while(que.size())que.pop_front();
		se.clear();
		sum=0;
	}
}a[MAX_QN];

int n;
prioriy_queue<int,vector<int>,greater<int> > que;

void insert(int p){
	int now=que.top();
	que.pop();
	
}

int main(){
	return 0;
}
