#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAX_N 500005
using namespace std;

int n;
typedef long long ll;
ll p[MAX_N],sumA[MAX_N],sumB[MAX_N];
char s[MAX_N];

ll tot;

ll work(){
	ll res=tot;
	sumA[0]=sumB[0]=0;
	for(int i=1;i<=n;i++){
		if(s[i]=='A')sumA[i]=sumA[i-1]+p[i],sumB[i]=sumB[i-1];
		else sumA[i]=sumA[i-1],sumB[i]=sumB[i-1]+p[i];
	}
	for(int i=1;i<=n;i++)
		res=max(res,tot-sumB[i]+sumA[i]);
	return res;
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%I64d",&p[i]);
	scanf("%s",s+1);
	for(int i=1;i<=n;i++)
		if(s[i]=='B')tot+=p[i];
	ll ans=work();
	reverse(p+1,p+1+n);reverse(s+1,s+1+n);
	ans=max(ans,work());
	cout<<ans<<endl;
	return 0;
}