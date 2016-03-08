#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
using namespace std;

bool check(int x){
	if(x%7==0)return true;
	while(x){
		if(x%10==7)return true;
		x/=10;
	}
	return false;
}

int main(){
	int T,n;
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		int pos,cnt=0;
		for(int i=1;;i++){
			if(check(i)){
				if(cnt==0)pos=i;
				cnt++;
			}
			else cnt=0;
			if(cnt==n)break;
		}
		printf("%d\n",pos);
	}
	return 0;
}