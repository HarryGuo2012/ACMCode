#include<stdio.h>
int main()
{
static char *a[][10]={"","I","II","III","IV","V","VI","VII","VIII","IX"
"","X","XX","XXX","XL","L","LX","LXX","LXXX","XCC",
"","C","CC","CCC","CD","D","DC","DCC","DCCC","CM"
}; /*建立对照表*/
int n,t,i,m;
printf("Please enter number:");
scanf("%d",&n); /*输入整数*/
printf("%d=",n);
for(m=0,i=1000;m<3;m++,i/=10)
{
t=(n%i)/(i/10); /*从高位向低位依次取各位的数字*/
printf("%s",a[2-m][t]); /*通过对照表翻译输出*/
}
printf(" ");
scanf("%d",&n);
}
