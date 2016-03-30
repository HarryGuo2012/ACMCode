#include <cstdio>
#include <vector>
#include <algorithm>

typedef std::pair<int, int> P;

std::vector<P> v;

bool check(int s){
	for(auto u : v){
		if(s < u.first)return false;
		s += u.second;
	}
	return true;
}

int n;

int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		P p;
		scanf("%d%d", &p.first, &p.second);
		v.push_back(p);
	}
	std::sort(v.begin(), v.end());
	int l = -1, r = 1000006;
	while(r - l > 1){
		int m = (r + l) >> 1;
		if(check(m))r = m;
		else l = m;
	}
	printf("%d\n", r);
	return 0;
}