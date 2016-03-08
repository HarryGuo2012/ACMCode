#include<bits/stdc++.h>
using namespace std;
template <class T>
inline bool scan_d(T &ret) {
   char c; int sgn;
   if(c=getchar(),c==EOF) return 0; //EOF
   while(c!='-'&&(c<'0'||c>'9')) c=getchar();
   sgn=(c=='-')?-1:1;
   ret=(c=='-')?0:(c-'0');
   while(c=getchar(),c>='0'&&c<='9') ret=ret*10+(c-'0');
   ret*=sgn;
   return 1;
}
const int maxn = 2e5+7;
long long d[maxn];
struct node
{
    int x,y;
    char c;
    int id;
}p[maxn];
int inq[maxn];
vector<int> X1;
vector<int> Y1;
vector<int> X[maxn];
vector<int> Y[maxn];
int vis[maxn][4];
int n;
long long T;
priority_queue<pair<long long,int>,vector<pair<long long,int> >,greater<pair<long long,int> > > Q;
int getar(char c)
{
    if(c=='U')return 0;
    if(c=='D')return 1;
    if(c=='L')return 2;
    if(c=='R')return 3;
}
int getX(int x)
{
    return lower_bound(X1.begin(),X1.end(),x)-X1.begin();
}
int getY(int x)
{
    return lower_bound(Y1.begin(),Y1.end(),x)-Y1.begin();
}
char s1[120];
int main()
{
    scanf("%d%lld",&n,&T);
    for(int i=1;i<=n;i++)
    {
        scan_d(p[i].x);scan_d(p[i].y);
        scanf("%s",s1);
        p[i].c = s1[0];
        p[i].id = i;
        X1.push_back(p[i].x);
        Y1.push_back(p[i].y);
    }

    sort(X1.begin(),X1.end());
    X1.erase(unique(X1.begin(),X1.end()),X1.end());

    sort(Y1.begin(),Y1.end());
    Y1.erase(unique(Y1.begin(),Y1.end()),Y1.end());

    for(int i=1;i<=n;i++)
    {
        X[getX(p[i].x)].push_back(p[i].id);
        Y[getY(p[i].y)].push_back(p[i].id);
    }
    for(int i=0;i<=n;i++)
        d[i]=T;
    d[1]=0;
    Q.push(make_pair(d[1],1));
    inq[1]=1;
    int tot = 0;
    while(!Q.empty())
    {
        if(tot>21000)break;
        tot++;
        pair<long long,int> temp = Q.top();
        int now = temp.second;
        Q.pop();
        inq[now]=0;
        if(vis[now][getar(p[now].c)])continue;
        vis[now][getar(p[now].c)]=1;
        if(d[now]<temp.first)continue;

        if(p[now].c=='U')
        {
            int dd = getX(p[now].x);
            for(int i=0;i<X[dd].size();i++)
            {
                int v = X[dd][i];
                if(v==now)continue;
                if(p[v].y>p[now].y)
                {
                    if(d[v]>d[now]+p[v].y-p[now].y)
                    {
                        d[v] = d[now]+p[v].y-p[now].y;
                        vis[v][getar(p[now].c)]=1;
                        Q.push(make_pair(d[v],v));
                    }
                }
            }
        }

        if(p[now].c=='D')
        {
            int dd = getX(p[now].x);
            for(int i=0;i<X[dd].size();i++)
            {
                int v = X[dd][i];
                if(v==now)continue;
                if(p[v].y<p[now].y)
                {
                    if(d[v]>d[now]-p[v].y+p[now].y)
                    {
                        d[v] = d[now]-p[v].y+p[now].y;
                        vis[v][getar(p[now].c)]=1;
                        Q.push(make_pair(d[v],v));
                    }
                }
            }
        }

        if(p[now].c=='R')
        {
            int dd = getY(p[now].y);
            for(int i=0;i<Y[dd].size();i++)
            {
                int v = Y[dd][i];
                if(v==now)continue;
                if(p[v].x>p[now].x)
                {
                    if(d[v]>d[now]+p[v].x-p[now].x)
                    {
                        d[v] = d[now]+p[v].x-p[now].x;
                        vis[v][getar(p[now].c)]=1;
                        Q.push(make_pair(d[v],v));
                    }
                }
            }
        }

        if(p[now].c=='L')
        {
            int dd = getY(p[now].y);
            for(int i=0;i<Y[dd].size();i++)
            {
                int v = Y[dd][i];
                if(v==now)continue;
                if(p[v].x<p[now].x)
                {
                    if(d[v]>d[now]-p[v].x+p[now].x)
                    {
                        d[v] = d[now]-p[v].x+p[now].x;
                        vis[v][getar(p[now].c)]=1;
                        Q.push(make_pair(d[v],v));
                    }
                }
            }
        }
    }

    for(int i=1;i<=n;i++)
    {
        if(p[i].c=='U')
            printf("%lld %lld\n",1LL*p[i].x,1LL*p[i].y+(T-d[i]));
        if(p[i].c=='D')
            printf("%lld %lld\n",1LL*p[i].x,1LL*p[i].y-(T-d[i]));
        if(p[i].c=='L')
            printf("%lld %lld\n",1LL*p[i].x-(T-d[i]),1LL*p[i].y);
        if(p[i].c=='R')
            printf("%lld %lld\n",1LL*p[i].x+(T-d[i]),1LL*p[i].y);
    }
    return 0;
}
