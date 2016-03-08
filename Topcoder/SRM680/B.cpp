#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
using namespace std;

class BearChairs{
public:
	vector <int> findPositions(vector <int> atLeast, int d){
		vector<int> a=atLeast;
		vector<int> b;
		b.push_back(a[0]);
		for(int i=1;i<a.size();i++){
			int u=a[i];
			bool flag=true;
			int ma=-1;
			for(int j=0;j<i;j++){
				if(abs(b[j]-u)<d)flag=false;
				ma=max(ma,b[j]);
			}
			//cout<<flag<<endl;
			if(flag)b.push_back(u);
			else b.push_back(ma+d);
		}
		return b;
	}
};

int main(){
	BearChairs bb;
	vector<int> a;
	int d;
	for(int i=0;i<4;i++){
		int x;
		cin>>x;
		a.push_back(x);
	}
	cin>>d;
	vector<int> v=bb.findPositions(a,d);
	for(int i=0;i<4;i++)
		cout<<v[i]<<" ";
	cout<<endl;
	cin>>d;
	return 0;
}