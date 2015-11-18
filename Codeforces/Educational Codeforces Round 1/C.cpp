#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#define MAX_N 100005
using namespace std;

const long double pi=acos(-1);

const long double eps=1e-8;

bool zero(long double x){
    return abs(x)<eps;
}

struct Vector{
    long double x,y;
    long double a;
    int id;
    Vector(long double xx,long double yy,int ii){
        x=xx;
        y=yy;
        id=ii;
        if(zero(x))
            a=pi/2;
        else
            a=atan(abs(y/x));
        if(x<0)a=pi-a;
        if(yy<=0)a=2*pi-a;
    }
    Vector(){}
};

bool cmp(Vector x,Vector y){
    return x.a<y.a;
}

Vector v[MAX_N];

int n;

int main(){
    cin.sync_with_stdio(false);
    cin>>n;
    for(int i=0;i<n;i++){
        long double x,y;
        cin>>x>>y;
        v[i]=Vector(x,y,i+1);
    }
    /*
    for(int i=0;i<n;i++)
        cout<<v[i].a<<" ";
    cout<<endl;
    */
    sort(v,v+n,cmp);
    long double ans=2*pi;
    int pos;
    for(int i=0;i<n-1;i++){
        if(v[i+1].a-v[i].a<ans)
            ans=v[i+1].a-v[i].a,pos=i;
    }
    long double tmp=v[n-1].a-v[0].a;
    if(tmp>pi)tmp=2*pi-tmp;
    if(tmp<ans)pos=n-1;
    cout<<v[pos].id<<" "<<v[(pos+1)%n].id<<endl;
    return 0;
}
