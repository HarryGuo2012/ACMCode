#include <windows.h>
#include <string>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <ctime>
#include <set>
using namespace std;
namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}
#define MAX_N 200005

int n,m;

int p[MAX_N];
set<int> se[MAX_N];

void solve(string str){
	for(int i = 0; i < MAX_N; i++)
		se[i].clear();
	str=str+".in";
	ofstream cout(str.c_str());
	n = 200000;
	cout << n << endl;
	for(int i = 1; i < n / 2; i++){
		p[i] = i - 1;
		cout << i - 1 << " ";
	}
	for(int i = n / 2; i < n - 100; i++){
		p[i] = n / 2 - 1;
		cout << n / 2 - 1 << " ";
	}
	for(int i = n - 100; i <= n; i++){
		int t = rand() % i;
		p[i] = t;
		cout << t << " ";
	}
	cout << endl;

	for(int i = 1; i < n / 2; i++){
		int t = rand() % 3 + 1;
		se[p[i]].insert(t);
		cout << t << " ";
	}
	for(int i = n / 2; i < n - 100; i++){
		se[p[i]].insert(i - n / 2 + 1);
		cout << i - n / 2 + 1 << " ";
	}
	for(int i = n - 100; i <= n; i++){
		int t = rand() % n + 1;
		while(se[p[i]].find(t) != se[p[i]].end()) t = rand() % n + 1;
		cout << t << " ";
	}
	cout << endl;
}	

int main(){
	for(int i=3;i<10;i++){
		std::string s=patch::to_string(i);
		if(s.length()==1)s="00"+s;
		else if(s.length()==2)s="0"+s;
		solve(s);
		string tmp="STD < "+s+".in > "+s+".out";
		system(tmp.c_str());
		//Sleep(100);
	}
	return 0;
}