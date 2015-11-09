#include<iostream>
#include<stdio.h>
#include<cmath>
using namespace std;

const double pi = acos(-1.0);
int t;double r,v,f,s;
int check(double x)
{
    double dist=x*v;
    double am=fmod(dist/2.0,2.0*r*pi);
    double dir=am/r;
    double cen=sin(dir);
    return dist+fabs(cen)*r*2.0>=f-s;
}
int main()
{
    scanf("%d",&t);
    cin>>r>>v;
    while(t--)
    {
        scanf("%lf%lf",&s,&f);
        double l=0.0,r=1999999999.0;
        for(int i=0;i<100;i++)
        {
            double mid=(l+r)/2.0;
            if(check(mid))r=mid;
            else l=mid;
        }
        printf("%.15f\n",l);
    }
}
