#include <string>
using namespace std;

class EllysTimeMachine{
public:
	string getTime(string s){
		int a = (s[0] - '0') * 10 + s[1] - '0';
		a %= 12;
		int b = (s[3] - '0') * 10 + s[4] - '0';
		a *= 5, b /= 5;
		if(b == 0) b = 12;
		string u = to_string(b), v = to_string(a);
		if(u.length() == 1) u = "0" + u;
		if(v.length() == 1) v = "0" + v;
		return u + ":" + v;
	}
};