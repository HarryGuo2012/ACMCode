#include<iostream>
#include<cstring>
#include<cstdio>
#include<list>
#include<vector>
#include<set>
#include<map>
#include<algorithm>
using namespace std;

int N;

typedef pair<int,int> P;

list<P> L;

int main(){
	while(scanf("%d",&N)==1){

		L.clear();
		P a;
		char c;
		while(N--){
			scanf("%d%d %c",&a.first,&a.second,&c);
			if(a.first>a.second)swap(a.first,a.second);
			for(list<P>::iterator it=L.begin();it!=L.end();){
				if(it->first>a.second||it->second<a.first)
					it++;
				else if(c=='w'){
					a.first=min(a.first,it->first);
					a.second=max(a.second,it->second);
					it=L.erase(it);
				}
				else if(c=='b'){
					if(a.first<=it->first&&it->second<=a.second)it=L.erase(it);
					else{
						if(it->first<a.first&&a.second<it->second){
							L.push_back(P(it->first,a.first-1));
							L.push_back(P(a.second+1,it->second));
							L.erase(it);
							break;
						}
						if(it->first<a.first&&a.first<=it->second)
							it->second=a.first-1;
						else
							it->first=a.second+1;
					}
				}
			}if(c=='w')
			L.push_back(a);
		}
		int ans=-1;
		long long u=12345678912,v;
		for(list<P>::iterator it=L.begin();it!=L.end();it++){
			int tmp=it->second-it->first;
			if(ans<tmp){
				u=it->first;
				v=it->second;
				ans=tmp;
			}
			else if(ans==tmp&&u>it->first){
				u=it->first;
				v=it->second;
			}
		}
		if(u!=12345678912)
			printf("%I64d %I64d\n",u,v);
		else 
			printf("Oh, my god\n");
	}
	return 0;
}
