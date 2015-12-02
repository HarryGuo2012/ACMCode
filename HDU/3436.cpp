#include<iostream>
#include<queue>
#include<vector>
#include<deque>
#include<cstring>
#include<set>
#include<algorithm>
#include<cmath>
#define MAX_N 100005
#define MAX_SN 333
using namespace std;

int T;

set<int> se[MAX_SN];

deque<int> que[MAX_SN];
/*
void output(){
	cout<<"----"<<endl;
	for(int i=0;i<5;i++,cout<<endl)
		for(auto it=que[i].begin();it!=que[i].end();it++)cout<<*it<<" ";
}
*/

int cas=0;

int main(){
	scanf("%d",&T);
	while(T--){
		int n,q;
		scanf("%d%d",&n,&q);
		printf("Case %d:\n",++cas);
		int mod=(int)sqrt(n)+1;
		//cout<<mod<<endl;
		for(int i=0;i<MAX_SN;i++)se[i].clear(),que[i].clear();
		for(int i=1;i<=n;i++){
			se[(i-1)/mod].insert(i);
			que[(i-1)/mod].push_back(i);
		}
		//output();
		while(q--){
			char s[6];
			int x;
			scanf("%s %d",s,&x);
			if(s[0]=='T'){
				int i=0;
				while(se[i].find(x)==se[i].end())i++;
				se[i].erase(x);
				int pre=x;
				for(int j=0;j<i;j++){
					se[j].insert(pre);
					que[j].push_front(pre);
					pre=*(que[j].end()-1);
					que[j].pop_back();
					se[j].erase(pre);
				}
				se[i].insert(pre);
				que[i].push_front(pre);
				deque<int>::iterator it=que[i].begin();
				for(;*it!=x;it++);
				que[i].erase(it);
				//output();
			}
			else if(s[0]=='R'){
				int sum=0,i=0;
				while(sum+que[i].size()<x)sum+=que[i++].size();
			//	cout<<i<<" "<<sum<<endl;
				x-=sum;
				deque<int>::iterator it=que[i].begin();
				for(int j=0;j<x-1;j++,it++);
				printf("%d\n",*it);
			}
			else{
				int i=0,sum=0;
				while(se[i].find(x)==se[i].end())sum+=que[i++].size();
				int j=sum;
			//	for(auto it=que[i].begin();it!=que[i].end();it++)cout<<*it<<" ";
			//	cout<<endl;
				deque<int>::iterator it=que[i].begin();
				while(*it!=x)it++,j++;
				printf("%d\n",j+1);
			}
		}
	}
	return 0;
}
