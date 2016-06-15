#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
#define MAXSIZE 10
#define TURE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERLOW -1
typedef struct 
{   int elem[MAXSIZE];
    int length;
}Seqlist;
void init_seqlist(Seqlist *l)
{   l->length=0;}                               //初始化线性表
int Insert_Seqlist(Seqlist *l,int i,int x)
{   int j;
    if(l->length==MAXSIZE)
    {   printf("full");
        return OVERLOW;
    }
    if(i<0||i>l->length+1)
    {   printf("wrong place");
        return ERROR;
    }
    for(j=l->length-1;j>=i;j--)
        l->elem[j+1]=l->elem[j];
        l->elem[i]=x;
        l->length++;
        return OK;
}                                           //顺序表插入
int Dlete_Seqlist(Seqlist *l,int i)
{   int j;
    if(i<1||i>l->length)
    {   printf("not exist");
        return ERROR;
    }
    for(j=i;j<=l->length-1;j++)
    {   l->elem[j]=l->elem[j+1];
        l->length--;
    }
    return OK;
}                                       //顺序表删除
void Create_Seqlist(Seqlist *l)
{
    int i,n,m;
    printf("输入表长:\n");
    scanf("%d",&n);
    l->length=n;
    printf("输入数值:\n");
    for(i=1;i<=n;i++)
    {   scanf("%d",&m);
        l->elem[i]=m;
    }
}                                       //顺序表创建
int Location(Seqlist *l,int x)
{   int i=1;
    while(i<=l->length&&l->elem[i]!=x)
        i++;
    if(i>l->length)
        return -1;
    else 
        return i;
}                                           //定位
void Print(Seqlist *l)
{   int i;
    printf("线性表变为：\n");
    for(i=1;i<=l->length;i++)
    {   printf("%2d",l->elem[i]);}
}                                       //打印顺序表
int main()
{   Seqlist a;
    int i,x,ch;
    init_seqlist(&a);
    Create_Seqlist(&a);
    printf("请输入：1.插入;2.删除\t");
    scanf("%d",&ch);
    switch(ch)
    {
        case 1:printf("请输入位置和数值：\n");
            scanf("%d%d",&i,&x);
            Insert_Seqlist(&a,i,x);
            break;
        case 2:printf("请输入删除的位置：\n");
            scanf("%d",&i);
            Dlete_Seqlist(&a,i);
            break;
        default:exit(0);
    }
    Print(&a);
    return 0;
}
