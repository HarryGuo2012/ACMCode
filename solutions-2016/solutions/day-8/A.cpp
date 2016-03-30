#include <string.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <algorithm>
#include <functional>
#include <utility>
#include <bitset>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstdio>

using namespace std;

#define REP(i,n) for((i)=0;(i)<(int)(n);(i)++)
#define snuke(c,itr) for(__typeof((c).begin()) itr=(c).begin();itr!=(c).end();itr++)

typedef long long ll;
#define MAX 1000000000000000000ll

vector <pair <ll, int> > normalize(vector <pair <ll, int> > v){
	int i,j;
	vector <pair <ll, int> > ans;
	int first = -1, second = -1;
	
	REP(i,v.size()){
		int c = v[i].second;
		if(c < second) continue;
		ans.push_back(v[i]);
		if(c > first){
			second = first;
			first = c;
		} else {
			second = c;
		}
	}
	
	return ans;
}

vector <pair <ll, int> > func(vector <pair <ll, int> > v, int p){
	int i,j;
	vector <pair <ll, int> > ans;
	
	REP(i,v.size()){
		ll x = v[i].first;
		for(j=0;;j++){
			ans.push_back(make_pair(x, v[i].second * (j + 1)));
			if(x > MAX / p) break;
			x *= p;
		}
	}
	
	sort(ans.begin(),ans.end());
	return ans;
}

int main(void){
	int i;
	
	vector <pair <ll, int> > v;
	v.push_back(make_pair(1, 1));
	
	for(int p=2;;p++){
		bool prime = true;
		for(i=2;i*i<=p;i++) if(p%i == 0) prime = false;
		if(!prime) continue;
		vector <pair <ll, int> > w = func(v, p);
		w = normalize(w);
		if(w == v) break;
		v = w;
	}
	
	int K;
	cin >> K;
	K--;
	
	if(K >= v.size()){
		cout << -1 << endl;
	} else {
		cout << v[K].first << endl;
	}
	
	return 0;
}
