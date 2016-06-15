#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int a;

int main() {
	while (cin >> a) {
		string s = "";
		while(a) {
			s = s + (char)('0' + (a & 1));
			a >>= 1;
		}
		reverse(s.begin(),s.end());
		cout << s << endl;
	}
	return 0;
}