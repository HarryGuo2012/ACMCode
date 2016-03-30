#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

vector<int> v;
int p;

bool check(int x){
	int ans = 0, pre = 0;
	for(int i = 0; i < v.size() - 1; i++){
		int t = v[i + 1] - v[i];
		if(t > x)
			ans += (i + 1 - pre) / 2, pre = i + 1;
	}
	return ans >= p;
}

class EllysSocks{
public:
	int getDifference(vector <int> S, int P){
		v = S;
		p = P;
		sort(v.begin(), v.end());
		v.push_back(INT_MAX - 5);
		int l = -1, r = INT_MAX >> 1;
		while(r - l > 1){
			int m = (r + l) >> 1;
			if(check(m)) r = m;
			else l = m;
		}
		return r;
	}
};