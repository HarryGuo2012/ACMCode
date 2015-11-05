/* **********************************************
Author      : kuangbin
Created Time: 2013/8/11 22:00:02
File Name   : F:\2013ACM��ϰ\ר��ѧϰ\�����ʷ�\SPOJ_QTREE.cpp
*********************************************** */

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <math.h>
#include <stdlib.h>
using namespace std;

typedef long long ll;

const ll Mod=1e18+23;

ll check(ll a,ll b){
	return (log(a)+log(b)>log(Mod))?Mod:a*b;
}

const ll MAXN = 200100;
struct Edge
{
    ll to,Next;
}edge[MAXN*2];
ll Head[MAXN],tot;
ll top[MAXN];//top[v]��ʾv���ڵ������Ķ��˽ڵ�
ll fa[MAXN]; //���׽ڵ�
ll deep[MAXN];//���
ll num[MAXN];//num[v]��ʾ��vΪ���������Ľڵ���
ll p[MAXN];//p[v]��ʾv���丸�׽ڵ���������߶����е�λ��
ll fp[MAXN];//��p�����෴
ll son[MAXN];//�ض���
ll pos;
void init()
{
    tot = 0;
    memset(Head,-1,sizeof(Head));
    pos = 0;
    memset(son,-1,sizeof(son));
}
void addedge(ll u,ll v)
{
    edge[tot].to = v;edge[tot].Next = Head[u];Head[u] = tot++;
}
void dfs1(ll u,ll pre,ll d) //��һ��dfs���fa,deep,num,son
{
    deep[u] = d;
    fa[u] = pre;
    num[u] = 1;
    for(ll i = Head[u];i != -1; i = edge[i].Next)
    {
        ll v = edge[i].to;
        if(v != pre)
        {
            dfs1(v,u,d+1);
            num[u] += num[v];
            if(son[u] == -1 || num[v] > num[son[u]])
                son[u] = v;
        }
    }
}
void getpos(ll u,ll sp) //�ڶ���dfs���top��p
{
    top[u] = sp;
    if(son[u] != -1)
    {
        p[u] = pos++;
        fp[p[u]] = u;
        getpos(son[u],sp);
    }
    else
    {
        p[u] = pos++;
        fp[p[u]] = u;
        return;
    }
    for(ll i = Head[u] ; i != -1; i = edge[i].Next)
    {
        ll v = edge[i].to;
        if(v != son[u] && v != fa[u])
            getpos(v,v);
    }
}

//�߶���
struct Node
{
    ll l,r;
    ll Max;
}segTree[MAXN*3];
void build(ll i,ll l,ll r)
{
    segTree[i].l = l;
    segTree[i].r = r;
    segTree[i].Max = 1;
    if(l == r)return;
    ll mid = (l+r)/2;
    build(i<<1,l,mid);
    build((i<<1)|1,mid+1,r);
}
void push_up(ll i)
{
    segTree[i].Max = check(segTree[i<<1].Max,segTree[(i<<1)|1].Max);	
}
void update(ll i,ll k,ll val) // �����߶����ĵ�k��ֵΪval
{
    if(segTree[i].l == k && segTree[i].r == k)
    {
        segTree[i].Max = val;
        return;
    }
    ll mid = (segTree[i].l + segTree[i].r)/2;
    if(k <= mid)update(i<<1,k,val);
    else update((i<<1)|1,k,val);
    push_up(i);
}
ll query(ll i,ll l,ll r)  //��ѯ�߶�����[l,r] �����ֵ
{
    if(segTree[i].l == l && segTree[i].r == r)
        return segTree[i].Max;
    ll mid = (segTree[i].l + segTree[i].r)/2;
	ll tmp;
    if(r <= mid)tmp=query(i<<1,l,r);
    else if(l > mid)tmp=query((i<<1)|1,l,r);
    else tmp=check(query(i<<1,l,mid),query((i<<1)|1,mid+1,r));
	return tmp;
}
ll find(ll u,ll v)//��ѯu->v�ߵ����ֵ
{
    ll f1 = top[u], f2 = top[v];
    ll tmp = 1;
    while(f1 != f2)
    {
        if(deep[f1] < deep[f2])
        {
            swap(f1,f2);
            swap(u,v);
        }
        tmp = check(tmp,query(1,p[f1],p[u]));
        u = fa[f1]; f1 = top[u];
    }
    if(u == v)return tmp;
    if(deep[u] > deep[v]) swap(u,v);
    ll t=check(tmp,query(1,p[son[u]],p[v]));
	return t;
}
ll e[MAXN][3];
int n,m;
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
	scanf("%d%d",&n,&m);
	init();
	for(ll i=0;i<n-1;i++){
      	scanf("%I64d%I64d%I64d",&e[i][0],&e[i][1],&e[i][2]);
       	addedge(e[i][0],e[i][1]);
       	addedge(e[i][1],e[i][0]);
	}
	dfs1(1,0,0);
    getpos(1,1);
    build(1,0,pos-1);
    for(ll i = 0;i < n-1; i++)
    {
      	if(deep[e[i][0]] > deep[e[i][1]])
 	       swap(e[i][0],e[i][1]);
   	    update(1,p[e[i][1]],e[i][2]);
	}
	while(m--){
		ll op;
		scanf("%I64d",&op);
		if(op==1){
			ll a,b;
			ll y;
			scanf("%I64d%I64d%I64d",&a,&b,&y);
			printf("%I64d\n",y/find(a,b));
		}
		else{
			ll a;
			ll b;
			scanf("%I64d%I64d",&a,&b);
			update(1,p[e[a-1][1]],b);
		}
	}
    return 0;
}
