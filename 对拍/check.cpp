#include<iostream>
#include<windows.h>
using namespace std;
int main()
{
    int t=100;
    while(t--)
    {
        system("Data > a+b.in");
        system("AC < a+b.in > AC.out");
        system("WA < a+b.in > WA.out");
        if(system("fc AC.out WA.out"))   break;
    }
    system("pause");
    return 0;
}