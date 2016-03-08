#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAX_N 2222
#define lowbit(x) (x&(-x))
using namespace std;

int T;
int n,a[MAX_N];
int d[5];

void f(){
	for(int i=1;i<=4;i++)
		d[i]=4-i+1;
	for(int i=1;i<=n;i++)
		a[i]=n-i+1;
}

void g(){
	reverse(d+1,d+5);
	reverse(a+1,a+1+n);
}

struct BitTree{
	int tree[MAX_N];
	void init(){
		memset(tree,0,sizeof(tree));
	}
	void add(int i,int x=1){
		while(i<MAX_N){
			tree[i]+=x;
			i+=lowbit(i);
		}
	}

	int sum(int i){
		int res=0;
		while(i){
			res+=tree[i];
			i-=lowbit(i);
		}
		return res;
	}
};

typedef long long ll;

ll _1234(){
	BitTree b1,b2;
	ll res=0;
	b1.init();b2.init();
	for(int i=1;i<=n;i++){
		b2.init();
		for(int j=n;j>=i+1;j--){
			if(a[j]>a[i])
				res=res+b1.sum(a[i])*(b2.sum(n)-b2.sum(a[j]));
			b2.add(a[j],1);
		}
		b1.add(a[i],1);
	}
	return res;
}

ll _1243(){
	BitTree b1,b2;
	ll res=0;
	b1.init();b2.init();
	for(int i=1;i<=n;i++){
		b2.init();
		for(int j=i+1;j<=n;j++){
			if(a[j]>a[i])
				res=res+b1.sum(a[i])*(b2.sum(n)-b2.sum(a[j]));
			b2.add(a[j],1);
		}
		b1.add(a[i],1);
	}
	return res;
}

ll _1324(){
	BitTree b1,b2;
	ll res=0;
	b1.init();b2.init();
	for(int i=1;i<=n;i++){
		b2.init();
		for(int j=n;j>=i+1;j--){
			if(a[i]>a[j])
				res=res+b1.sum(a[j])*(b2.sum(n)-b2.sum(a[i]));
			b2.add(a[j]);
		}
		b1.add(a[i]);
	}
	return res;
}

ll _1342(){
	BitTree b1,b2;
	ll res=0;
	b1.init();b2.init();
	for(int i=1;i<=n;i++){
		b2.init();
		for(int j=i+1;j<=n;j++){
			if(a[i]>a[j])
				res=res+b1.sum(a[j])*(b2.sum(n)-b2.sum(a[i]));
			b2.add(a[j]);
		}
		b1.add(a[i]);
	}
	return res;
}

ll _1423(){
	BitTree b1,b2;
	ll res=0;
	b1.init();b2.init();
	for(int i=1;i<=n;i++){
		b2.init();
		for(int j=n;j>=i+1;j--){
			if(a[i]>a[j])
				res=res+b1.sum(a[j])*(b2.sum(a[i])-b2.sum(a[j]));
			b2.add(a[j]);
		}
		b1.add(a[i]);
	}
	return res;
}

ll _1432(){
	BitTree b1,b2;
	ll res=0;
	b1.init();b2.init();
	for(int i=1;i<=n;i++){
		b2.init();
		for(int j=i+1;j<=n;j++){
			if(a[i]>a[j])
				res=res+b1.sum(a[j])*(b2.sum(a[i])-b2.sum(a[j]));
			b2.add(a[j]);
		}
		b1.add(a[i]);
	}
	return res;
}

ll _2143(){
	BitTree b1,b2;
	ll res=0;
	b1.init();b2.init();
	for(int i=n;i>=1;i--){
		b2.init();
		for(int j=i-1;j>=1;j--){
			if(a[i]>a[j])
				res=res+(b1.sum(a[i])-b1.sum(a[j]))*b2.sum(a[j]);
			b2.add(a[j]);
		}
		b1.add(a[i]);
	}
	return res;
}

ll _2413(){
	BitTree b1,b2;
	ll res=0;
	b1.init();b2.init();
	for(int i=1;i<=n;i++){
		for(int j=0;j<MAX_N;j++)
			b2.tree[j]=b1.tree[j];
		for(int j=1;j<=i-1;j++){
			if(a[i]>a[j])
				res=res+(b2.sum(n)-b2.sum(a[i]))*b1.sum(a[j]);
			b2.add(a[j],-1);
		}
		b1.add(a[i]);
	}
	return res-_2143();
}

int main(){
	long long res;
	scanf("%d",&n);
	int p=0;
	for(int i=1;i<=4;i++)
		scanf("%d",&d[i]);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	if(d[1]>2)f();
	if(d[1]==2){
		if(d[4]==4){f();g();}
		else if(d[4]==1)g();
	}
	for(int i=1;i<=4;i++)
		p=p*10+d[i];
	//cout<<p<<endl;
	switch(p){
		case 1234:res=_1234();break;
		case 1243:res=_1243();break;
		case 1324:res=_1324();break;
		case 1342:res=_1342();break;
		case 1423:res=_1423();break;
		case 1432:res=_1432();break;
		case 2143:res=_2143();break;
		case 2413:res=_2413();break;
	}
	printf("%lld\n",res);
	cin>>n;
	return 0;
}