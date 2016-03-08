#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <set>
#include <map>
#define MAX_N 1003
using namespace std;

int n;
long long a[MAX_N];
map<long long,int> ma;
vector<long long> ve;

int zero=0;

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%I64d",&a[i]);
		if(a[i]==0)zero++;
	}
	for(int i=1;i<=n;i++)
		ma[a[i]]++;
	int ans=2,x,y;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			if(i==j||(a[i]==0&&a[j]==0))continue;
			ve.clear();
			if(ma[a[i]]>0){ve.push_back(a[i]);ma[a[i]]--;}
			if(ma[a[j]]>0){ve.push_back(a[j]);ma[a[j]]--;}
			long long u=a[i],v=a[j];
			int cnt=2;
			while(ma[u+v]>0){
				long long tmp=v;
				v=u+v;
				ve.push_back(v);ma[v]--;
				u=tmp;
				cnt++;
			}
			for(int k=0;k<ve.size();k++)ma[ve[k]]++;
			if(ans<cnt)ans=cnt,x=i,y=j;
		}
	cout<<max(zero,ans)<<endl;
	return 0;
}