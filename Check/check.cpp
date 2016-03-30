#include <windows.h>
#include <fstream>
using namespace std;
int main()
{
    while(1)
    {
        system("Data > a+b.in");
        system("AC < a+b.in > AC.out");
        system("WA < a+b.in > WA.out");
        if(system("fc AC.out WA.out"))   break;
    }
    system("pause");
    return 0;
}