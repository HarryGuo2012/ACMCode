#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<vector>
using namespace std;

int T;
int n,s;

vector<int> a,b;

int main(){
	scanf("%d",&T);
	while(T--){
		bool flag=true;
		scanf("%d%d",&n,&s);
		if(s==0){
			if(n==1)printf("0 0\n");
			else printf("-1 -1\n");
			continue;
		}
		a.clear();
		b.clear();
		int sum=0;
		for(int i=0;i<n;i++){
			int l=(n-i-1);
			int j=(i==0);
			while(sum+j+l*9<s)j++;
			if(j>=10){
				flag=false;
				break;
			}
			a.push_back(j);
			sum+=j;
		}
		sum=0;
		for(int i=0;i<n;i++){
			int j=9;
			while(sum+j>s)j--;
			if(j<0||(i==0&&j==0)){
				flag=false;
				break;
			}
			b.push_back(j);
			sum+=j;
		}
		if(sum!=s)flag=false;
		if(flag){
			for(int i=0;i<a.size();i++)printf("%d",a[i]);
			printf(" ");
			for(int i=0;i<b.size();i++)printf("%d",b[i]);
			printf("\n");
		}
		else printf("-1 -1\n");
	}
	return 0;
}
