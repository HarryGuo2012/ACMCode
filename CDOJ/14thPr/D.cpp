#include <iostream>
#include <cstdio>

using namespace std;

int t;
long long add[2][13]={{0,31,28,31,30,31,30,31,31,30,31,30,31},{0,31,29,31,30,31,30,31,31,30,31,30,31}};
long long a,b,c,num[2],sum,A,B,C,pd;

long long min(long long num1,long long num2)
{
    if(num1<num2)return num1;
    return num2;
}

void cal(int x)
{
    if(a>2017)num[x]+=(a-2017)/400*sum;
    A=2016;B=2;C=1;
    if(b!=1)
    {
        for(int i=2016;i<=2017+(a-2017)%400;i++)
        {
            if(i==2017+(a-2017)%400)pd=b;
            else pd=12;
            for(int j=1;j<=pd;j++)
            {
                if(i==2017+(a-2017)%400 && j==pd-1)
                {
                    if(C%7==1)num[x]+=min(7,c);
                    break;
                }
                if(C%7==1)num[x]+=7;
                if(B==2)
                {
                    if(A%100==0)
                    {
                        if(A%400==0)C+=add[1][B];
                        else C+=add[0][B];
                    }
                    else if(A%4==0)C+=add[1][B];
                    else C+=add[0][B];
                }
                else C+=add[0][B];
                B++;if(B==13){B=1;A++;}
            }
        }
    }
    else
    {
        for(int i=2016;i<=2016+(a-2017)%400;i++)
        {
            for(int j=1;j<=12;j++)
            {
                if(i==2016+(a-2017)%400 && j==12)
                {
                    if(C%7==1)num[x]+=min(7,c);
                    break;
                }
                if(C%7==1)num[x]+=7;
                if(B==2)
                {
                    if(A%100==0)
                    {
                        if(A%400==0)C+=add[1][B];
                        else C+=add[0][B];
                    }
                    else if(A%4==0)C+=add[1][B];
                    else C+=add[0][B];
                }
                else C+=add[0][B];
                B++;if(B==13){B=1;A++;}
            }
        }
    }
}

int main()
{
    a=2016;b=2;c=1;
    for(int i=1;i<=400;i++)
    {
        for(int j=1;j<=12;j++)
        {
            if(c%7==1)sum+=7;
            if(b==2)
            {
                if(a%100==0)
                {
                    if(a%400==0)c+=add[1][b];
                    else c+=add[0][b];
                }
                else if(a%4==0)c+=add[1][b];
                else c+=add[0][b];
            }
            else c+=add[0][b];
            b++;if(b==13){b=1;a++;}
        }
        //cout<<sum<<endl;
    }
    scanf("%d",&t);
    while(t--)
    {
        num[0]=num[1]=0;
        scanf("%lld%lld%lld",&a,&b,&c);
        c--;
        if(c==0)
        {
            if(b==1){b=12;a--;c=31;}
            else if(b==2){b--;c=31;}
            else if(b==3)
            {
                b--;
                if(a%100==0)
                {
                    if(a%400==0)c=29;
                    else c=28;
                }
                else if(a%4==0)c=29;
                else c=28;
            }
            else if(b==4){b--;c=31;}
            else if(b==5){b--;c=30;}
            else if(b==6){b--;c=31;}
            else if(b==7){b--;c=30;}
            else if(b==8){b--;c=31;}
            else if(b==9){b--;c=31;}
            else if(b==10){b--;c=30;}
            else if(b==11){b--;c=31;}
            else if(b==12){b--;c=30;}
        }
        if(a==2016 && b==1 && c==31)num[0]=0;
        else cal(0);
        scanf("%lld%lld%lld",&a,&b,&c);
        cal(1);
        printf("%lld\n",num[1]-num[0]);
    }
    return 0;
}