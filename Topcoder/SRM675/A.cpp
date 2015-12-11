#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;

vector<int> res;

void add_edge(int x,int y){
	res.push_back(x);
	res.push_back(y);
}

class TreeAndPathLength3{
public:
	vector <int> construct(int s){
		
		if(s<500){
			for(int i=0;i<=s+1;i++){
				res.push_back(i);
				res.push_back(i+1);
			}
			return res;
		}
		
		add_edge(0,1);
		int k=1;
		while(k*k+k<s)k++;
		if(k*k+k!=s)k--;
		for(int i=2;i<=k+1;i++)
			add_edge(i,0);
		for(int i=k+2;i<=2*k+1;i++)
			add_edge(i,1);
		int now=2*k+2;
		add_edge(2,now);
		s-=k*k+k;
		while(s--){add_edge(now,now+1);now++;}
		return res;
	}
};

int main(){
	TreeAndPathLength3 t;
	vector<int> v=t.construct(9497);
	for(int i=0;i<v.size();i++)cout<<v[i]<<" ";
	cout<<endl;
	return 0;
}
