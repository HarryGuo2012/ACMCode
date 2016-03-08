#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
#define MAX_N 50004
using namespace std;

struct Line{
	int a,b,c;
	Line(int aa,int bb,int cc):a(aa),b(bb),c(cc){}
	Line(){}
};

bool cmp(Line x,Line y){
	return x.b<y.b;
}

Line h[MAX_N];

int tree[MAX_N];

void add(int i,int x){
	while(i<MAX_N){
		tree[i]+=x;
		i+=i&(-i);
	}	
}

int sum(int i){
	int res=0;
	while(i){
		res+=tree[i];
		i-=i&(-i);
	}
	return res;
}

int n;

bool vis[MAX_N];
int cnt=0;

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d%d",&h[i].a,&h[i].b,&h[i].c);
		h[i].a++;h[i].b++;
	}
	sort(h+1,h+1+n,cmp);
	for(int i=1;i<=n;i++){
		int tmp=sum(h[i].b)-sum(h[i].a-1);
		for(int j=h[i].b;j>=h[i].a;j--){
			if(tmp>=h[i].c)break;
			if(vis[j])continue;
			vis[j]=1;
			tmp++;
			cnt++;
			add(j,1);
		}
	}
	cout<<cnt<<endl;
	return 0;
}
