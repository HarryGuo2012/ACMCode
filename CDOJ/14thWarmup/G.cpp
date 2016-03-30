#include <cstdio>
#include <vector>
#include <algorithm>

int n, m, k;
std::vector<int> v;

int main(){
	scanf("%d%d%d", &n, &m, &k);
	if(m == 1 || n == 1){
		printf("-1\n");
		return 0;
	}
	if(m >= n){
		if((n - 1) * n / 2 < k){
			printf("-1\n");
			return 0;
		}
	}
	else{
		if((2 * n - m) * (m - 1) / 2 < k){
			printf("-1\n");
			return 0;
		}
	}
	int minNum = m;
	for(int i = 0; i < n; i++){
		v.push_back(std::max(m, 1));
		minNum = std::min(minNum, v[i]);
		m--;
	}
	int p = 0, cnt = 0;
	for(int j = 0; j < k; j++){
		if(p == n - 1 - cnt){
			p = 0;
			cnt++;
		}
		std::swap(v[p], v[p + 1]);
		p++;
	}
	for(int i = v.size() - 1; i >= 0; i--)
		printf("%d%c", v[i], i == 0 ? '\n' : ' ');
	return 0;
}	