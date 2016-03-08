#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <string>
#include <queue>
using namespace std;

priority_queue<int> que;
int cnt[30];
class Istr{
public:
	int count(string s,int k){
		for(int i=0;i<s.length();i++)
			cnt[s[i]-'a']++;
		for(int i=0;i<26;i++)if(cnt[i])que.push(cnt[i]);
		for(int i=0;i<k;i++){
			if(que.size()==0)
				return 0;
			int t=que.top();que.pop();
			if(t>1)
				que.push(t-1);
		}
		int ans=0;
		while(que.size()){
			ans+=que.top()*que.top();
			que.pop();
		}
		return ans;
	}
};