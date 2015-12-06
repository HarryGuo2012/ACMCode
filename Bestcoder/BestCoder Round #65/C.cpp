#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAX_N 100005
#define maxn MAX_N
using namespace std;

#define lowbit(x) ((x)&(-x))
int val[maxn],sz;

void init(int s){
	sz=s;
	memset(val , 0 , sizeof(int)*(sz+5));
}
void updata(int pos ,int key){
	while(pos<=sz){
		val[pos]+=key;
		pos+=lowbit(pos);	
	}
}

int prefixsum(int pos){
	int res=0;
	while(pos>0){
		res+=val[pos];
		pos-=lowbit(pos);
	}		
	return res;
}
int query(int l,int r){
	return prefixsum(r)-prefixsum(l-1);
}

	//到第一个大于等于k的位置返回
	//若不存在,返回-1
int lower_bound(int k){
	if(prefixsum(sz)<k) return -1;
	int l = 1 , r = sz;
	while(l <= r){
		int mid = l + ((r-l)>>1);
		if(prefixsum(mid) < k) l = mid + 1;
		else r = mid - 1;
	}
	return l;
}
	
long long a[MAX_N],b[MAX_N];
int c[MAX_N];

int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		int n;
		scanf("%d",&n);
		init(n);
		for(int i = 1 ; i <= n ;i++) 
			scanf("%lld",&a[i]);
		for(int i = 1 ; i <= n ;i++) 
			b[i] =a[i]-a[i-1];
		for(int i = 1 ; i <= n ;i++) 
			updata(i , 1);
		for(int i = n ; i >= 1 ;i--){
			int tmp = i - b[i],id = lower_bound(tmp);
			c[i] = id;
			updata(id,-1);
		}
		printf("%d",c[1]);
		for(int i = 2 ; i <= n ; ++ i) printf(" %d",c[i]);
		printf("\n");
	}
	return 0;
}


