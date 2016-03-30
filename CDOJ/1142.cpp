#include <cstdio>
#include <vector>
#include <algorithm>

typedef long long ll;

std::vector<ll> num, sum;

int n;

int main(){
	while(true){
		scanf("%d", &n);
		if(n == 0) break;
		num.clear();
		sum.clear();
		for(int i = 0; i < n; i++){
			ll a;
			scanf("%lld", &a);
			num.push_back(a);
		}
		for(auto u : num)
			for(auto v : num)
				if(u != v)
					sum.push_back(u + v);

		std::sort(num.begin(), num.end());
		std::sort(sum.begin(), sum.end());

		ll ans = -536870912;
		bool flag = false;

		for(auto c : num)
			for(auto d : num){
				if(c == d) continue;

				ll t = d - c;
				auto itUp = std::lower_bound(sum.begin(), sum.end(), t + 1);
				auto itLo = std::lower_bound(sum.begin(), sum.end(), t);
				if(itLo == sum.end() || *itLo != t) continue;
				ll tmp = itUp - itLo;
				t = d - 2 * c;
				itUp = std::lower_bound(num.begin(), num.end(), t + 1);
				itLo = std::lower_bound(num.begin(), num.end(), t);
				if(itLo == num.end() || *itLo != t){
					flag = true;
					ans = std::max(ans, d);
					continue;
				}
				tmp -= 2 * (itUp - itLo);
				if(tmp){
					flag = true;
					ans = std::max(ans, d);
				}
			}

		if(flag == 0)
			printf("no solution\n");
		else
			printf("%lld\n", ans);
	}
	return 0;
}