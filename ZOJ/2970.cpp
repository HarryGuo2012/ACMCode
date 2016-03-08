#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>
#include <cstdio>
using namespace std;

int main(){
	string s;
	int T;
	scanf("%d",&T);
	while(T--){
		int n;
		cin>>s;
		int ma=-1,mi=2012;
		scanf("%d",&n);
		for(int i=0;i<n;i++){
			int a;
			scanf("%d",&a);
			ma=max(ma,a),mi=min(mi,a);
		}
		if(s[0]=='F')printf("%d\n",mi);
		else printf("%d\n",ma);
	}
	return 0;
}