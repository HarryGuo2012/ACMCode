#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <cmath>
using namespace std;

struct point
{
    long double x,y;
}a[55];
long double r;    //半径

long double dist_1point(long double x0,long double y0)    //点到原点距离
{
    return sqrt(x0*x0+y0*y0);
}
long double dist_2point(long double x1,long double y1,long double x2,long double y2) //两点距离
{
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
long double dist_line(long double x1,long double y1,long double x2,long double y2)    //直线到原点距离
{
    long double A,B,C,dist;
    A=y1-y2;
    B=x1-x2;
    C=x1*y2-x2*y1;
    dist=fabs(C)/sqrt(A*A+B*B);    //直线到原点距离公式
    return dist;
}
long double get_cos(long double a,long double b,long double c)  //余弦定理求角度
{
    long double angel=(b*b+c*c-a*a)/(2*b*c);
    return angel;
}
point get_point(long double x0,long double y0)    //计算点与原点的直线与圆相交的交点
{
    long double k;
    point temp;
    if(x0!=0)    //若斜率存在
    {
        k=y0/x0;
        temp.x=fabs(r)/sqrt(1+k*k);    //判断是两个点的哪一个
        if(x0<0) temp.x=-temp.x;    //temp.x应该与x0同符号
        temp.y=k*temp.x;
    }
    else        //斜率不存在
    {
        temp.x=0;
        if(y0>0) temp.y=r;        //判断是两个点的哪一个
        else temp.y=-r;            //temp.y应该与y0同符号
    }
    return temp;
}
int fi(long double x1,long double y1,long double x2,long double y2)        //关键啊啊啊！！！！
{
    if (x1*y2-x2*y1>0) return 1;        //判断是相加还是相减
    else return -1;
}

long double get_area(long double x1,long double y1,long double x2,long double y2) //三角剖分
{
    int sign=fi(x1,y1,x2,y2);    //判断三角形面积加还是减
    long double s;    //总面积
    long double l=dist_line(x1,y1,x2,y2);       //l = 直线ab与原点距离
    long double a=dist_1point(x1,y1);           //a = 线段a长度
    long double b=dist_1point(x2,y2);           //b = 线段b长度
    long double c=dist_2point(x1,y1,x2,y2);     //c = 线段c长度
    if(a==0 || b==0)
        return 0;    //若其中一条边为0，返回面积0

    //第一种情况：三角形的两条边a、b全部短于半径。
    if(a<=r && b<=r)
    {
        s=fabs(x1*y2-x2*y1)/2.0;
        return s*sign;
    }

    //第二种情况：a、b两条边长于半径，l也长于半径。
    else if(a>=r && b>=r && l>=r)
    {
        point t1=get_point(x1,y1);
        point t2=get_point(x2,y2);
        long double d=dist_2point(t1.x,t1.y,t2.x,t2.y);
        long double sita1=acos(get_cos(d,r,r));
        long double s=fabs(sita1*r*r/2.0); //扇形面积：s=θ*r*r/2
        return s*sign;
    }

    //第三种情况：a、b两条边长于半径，但l短于半径，并且垂足落在这条边上。
    else if(a>=r && b>=r && l<=r && (get_cos(a,b,c)<=0 || get_cos(b,a,c)<=0))
    {
        point t1=get_point(x1,y1);
        point t2=get_point(x2,y2);
        long double d=dist_2point(t1.x,t1.y,t2.x,t2.y);
        long double sita=acos(get_cos(d,r,r));
        s=fabs(sita*r*r/2.0);
        return s*sign;
    }

    //第四种情况：a、b两条边长于半径，但l短于半径，且垂足没有落在这条边上。
    else if(a>=r && b>=r && l<=r && (get_cos(a,b,c)>0 && get_cos(b,a,c)>0))
    {
        long double xx1,xx2,yy1,yy2;    //点(x1,y1)与(x2,y2)组成的直线与圆的交点
        if(x1!=x2)    //若斜率存在
        {
            long double k12=(y1-y2)/(x1-x2);
            long double b12=y1-k12*x1;
            long double a0=(1+k12*k12);
            long double b0=(2*k12*b12);
            long double c0=(b12*b12-r*r);
            //化成一元二次方程，用公式求出两个交点
            xx1=(-b0+sqrt(b0*b0-4*a0*c0))/(2*a0);
            yy1=k12*xx1+b12;
            xx2=(-b0-sqrt(b0*b0-4*a0*c0))/(2*a0);
            yy2=k12*xx2+b12;
        }
        else    //若斜率不存在 x1==x2
        {
            xx1=x1;
            xx2=x1;
            yy1=sqrt(r*r-x1*x1);
            yy2=-sqrt(r*r-x1*x1);
        }
        point t1=get_point(x1,y1);        //(x1,y1),(0,0)组成直线与圆的交点
        point t2=get_point(x2,y2);        //(x2,y2),(0,0)组成直线与圆的交点
        long double d1=dist_2point(xx1,yy1,xx2,yy2);    //直线1与原点距离
        long double d2=dist_2point(t1.x,t1.y,t2.x,t2.y);    //直线2与原点距离
        long double sita1=acos(get_cos(d1,r,r));  //小的扇形弧度
        long double sita2=acos(get_cos(d2,r,r));     //大的扇形弧度
        long double s1=fabs(sita1*r*r/2.0);   //小的扇形面积
        long double s2=fabs(sita2*r*r/2.0);   //大的扇形面积
        long double s3=fabs(xx1*yy2-xx2*yy1)/2.0;  //三角形面积
        s=s2+s3-s1;        //相交面积
        return s*sign;
    }

    //第五种情况1：三角形的两条边一条长于半径，另外一条短于半径
    else if(a>=r && b<=r)    //a长于半径，b短于半径
    {
        long double xxx,yyy;
        if(x1!=x2)    //斜率存在
        {
            long double k12=(y1-y2)/(x1-x2);
            long double b12=y1-k12*x1;
            long double a0=(1+k12*k12);
            long double b0=(2*k12*b12);
            long double c0=(b12*b12-r*r);
            //化成一元二次方程，用公式求出两个交点
            long double xx1=(-b0+sqrt(b0*b0-4*a0*c0))/(2*a0);
            long double yy1=k12*xx1+b12;
            long double xx2=(-b0-sqrt(b0*b0-4*a0*c0))/(2*a0);
            long double yy2=k12*xx2+b12;
            //判断两个交点中的哪一个，应在(x1,x2)两点之间
            if(x1<=xx1 && xx1<=x2 || x2<=xx1 && xx1<=x1) {xxx=xx1; yyy=yy1;}
            else {xxx=xx2; yyy=yy2;}
        }
        else    //斜率不存在 x1==x2
        {
            long double xx1=x1;
            long double yy1=-sqrt(r*r-x1*x1);
            long double yy2=sqrt(r*r-x1*x1);
            //判断两个交点中的哪一个，应在(y1,y2)两点之间
            if(y1<=yy1 && yy1<=y2 || y2<=yy1 && yy1<=y1) {yyy=yy1; xxx=xx1;}
            else {yyy=yy2; xxx=xx1;}
        }
        //判断交点(该点已判断方向)
        point t1=get_point(x1,y1);
        long double ddd=dist_2point(t1.x,t1.y,xxx,yyy);
        long double sita1=acos(get_cos(ddd,r,r));
        long double s1=fabs(sita1*r*r/2.0);
        long double s3=fabs(xxx*y2-yyy*x2)/2.0;
        s=s1+s3;    //相交面积
        return s*sign;
    }

    //第五种情况2：三角形的两条边一条长于半径，另外一条短于半径，与上述同理！！！
    else if(a<=r && b>=r)    //a短于半径，b长于半径
    {
        long double xxx,yyy;        //与上述同理！！！
        if(x1-x2!=0)
        {
            long double k12=(y1-y2)/(x1-x2);
            long double b12=y1-k12*x1;
            long double a0=(1+k12*k12);
            long double b0=(2*k12*b12);
            long double c0=(b12*b12-r*r);
            long double xx1=(-b0+sqrt(b0*b0-4*a0*c0))/(2*a0);
            long double yy1=k12*xx1+b12;
            long double xx2=(-b0-sqrt(b0*b0-4*a0*c0))/(2*a0);
            long double yy2=k12*xx2+b12;
            if(x1<=xx1 && xx1<=x2 || x2<=xx1 && xx1<=x1) {xxx=xx1; yyy=yy1;}
            else {xxx=xx2; yyy=yy2;}
        }
        else
        {
            long double yy1=-sqrt(r*r-x1*x1);
            long double yy2=sqrt(r*r-x1*x1);
            long double xx1=x1;
            if(y1<=yy1 && yy1<=y2 || y2<=yy1 && yy1<=y1) {yyy=yy1; xxx=xx1;}
            else {yyy=yy2; xxx=xx1;}
        }
        point t1=get_point(x2,y2);
        long double ddd=dist_2point(t1.x,t1.y,xxx,yyy);
        long double sita1=acos(get_cos(ddd,r,r));
        long double s1=fabs(sita1*r*r/2.0);
        long double s3=fabs(xxx*y1-yyy*x1)/2.0;
        s=s1+s3;
        return s*sign;
    }
    else return 0;
}

int main()
{
    int T, n;
    scanf("%d", &T);
    int cas = 0;
    while(T--){
        n = 4;
        long double cx, cy;
        cin>>cx>>cy>>r>>a[0].x>>a[0].y>>a[2].x>>a[2].y;
         if(r <= 0){
            printf("Case #%d: 0.000\n", ++cas);
            continue;
        }
        a[1].x = a[2].x;
        a[1].y = a[0].y;
        a[3].x = a[0].x;
        a[3].y = a[2].y;
        for(int i = 0; i < n; i++)
            a[i].x -= cx, a[i].y -= cy;
        a[n] = a[0];
        long double area = 0;
        for(int i=0;i<n;i++)
        {
            area+=get_area(a[i].x,a[i].y,a[i+1].x,a[i+1].y);
        }
        cout<<"Case #"<<++cas<<": ";
        cout<<fixed<<setprecision(4)<<fabs(area)<<endl;
        //printf("Case #%d: %.4f\n", ++cas, fabs(area));
    }
    return 0;
}