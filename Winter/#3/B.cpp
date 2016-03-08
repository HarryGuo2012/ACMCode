#include<cstdio>
#define f(i,n) for(i=1;i<=n;i++)
#define s(a,b) scanf("%I64d%I64d",&a,&b);
long long x[200005],w[200005],D,j,i,m,o,u,v,p,n;
int main(){
	s(n,D)f(i,n)s(x[i],w[i])
	m=o=u=v=-1;j=1;
	f(i,n){while(x[i]-x[j]>=D){if(m<w[j])m=w[j],p=j;j++;}
		if(m!=-1&&m+w[i]>o)
			o=m+w[i],u=p,v=i;
	}
	printf("%I64d %I64d\n",u,v);
}
