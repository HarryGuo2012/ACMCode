#include<math.h>  
#include<stdio.h>  
#include<string.h>  
#include <ctime>
#include<algorithm>  
#define N 11000  
using namespace std;  
const double EPS=1e-10;  
const double INF=1e100;  
struct Point  
{  
    double x,y;  
    Point(){}  
    Point(double _,double __):x(_),y(__){}  
    void read()  
    {  
        scanf("%lf%lf",&x,&y);  
    }  
    friend Point operator +(Point a,Point b)  
    {  
        return Point(a.x+b.x,a.y+b.y);  
    }  
    friend Point operator -(Point a,Point b)  
    {  
        return Point(a.x-b.x,a.y-b.y);  
    }  
    friend double operator *(Point a,Point b)  
    {  
        return a.x*b.x+a.y*b.y;  
    }  
    friend double dis2(Point a,Point b)  
    {  
        return (a-b)*(a-b);  
    }  
}p[N];  
double X,Y;  
int n;  
double drand()  
{  
    return rand()%10000/10000.0;  
}  
double calc(Point a)  
{  
    double ret=INF;  
    for(int i=1;i<=n;i++)  
    {  
        ret=min(ret,dis2(a,p[i]));  
    }  
    return -ret;  
}  
void slove(Point& ans,double T)  
{  
    Point next,dt;  
    double E,nE,dE;  
    E = calc(ans);
    while(T>EPS)  
    {  
        double u = drand();
        double v = drand();
        printf("---%f %f\n", u, v);
        dt=Point((u*2-1.0)*T,(v*2-1.0)*T);  
        next=ans+dt;  
        next.x=min(X,max(0.0,next.x)),next.y=min(Y,max(0.0,next.y));  
        printf("%f %f\n", next.x, next.y);
        nE=calc(next);  
        dE=nE-E;  
        if (dE > 0)
            printf("%f\n", exp(-dE/T));
        if(dE<0||drand()<exp(-dE/T)) {  
            //printf("%f\n", exp(-dE/T));
            ans=next,E=nE;  
        }
        T*=0.99140142;  
        printf("%f\n", T);
        printf("%f %f\n", ans.x, ans.y);
        int a;scanf("%d", &a);
    }  
}  
int main()  
{  
    srand(1234);  
    int c,T,m,i,j,k;  
    Point ans;  
    scanf("%d",&T);  
    for(c=1;c<=T;c++)  
    {  
        scanf("%lf%lf%d",&X,&Y,&n);  
        for(i=1;i<=n;i++)  
            p[i].read();  
        ans=Point(X/2,Y/2);  
        slove(ans,max(X,Y)/2);  
        printf("The safest point is (%.1f, %.1f).\n",ans.x,ans.y);  
    }  
    return 0;  
}  

