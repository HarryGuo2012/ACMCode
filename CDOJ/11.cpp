#include <iostream>
#include <string>
#include <cstring>

#define MAX_N 10
#define MAX_C 26

int n;
std::string s;
int cnt[MAX_N][MAX_C], cnt2[MAX_C];

std::string name;

int main(){
	int T, cas = 0;
	std::cin >> T;
	while(T--){
		int ans = 0;
		memset(cnt, 0, sizeof(cnt));
		memset(cnt2, 0, sizeof(cnt2));
		std::cin >> s >> n;
		for(auto c : s)
			cnt2[c - 'a']++;
		for(int i = 0; i < n; i++){
			std::cin >> name;
			for(auto c : name)
				cnt[i][c - 'a']++;
		}

		for(int mask = 0; mask < (1 << n); mask++){
			bool flag = true;
			for(int i = 0; i < 26; i++){
				int sum = 0;
				for(int j = 0; j < n; j++)
					if(mask >> j & 1)
						sum += cnt[j][i];
				if(sum > cnt2[i]){
					flag = false;
					break;
				}
			}
			if(flag)
				ans = std::max(ans, (int)__builtin_popcount(mask));
		}
		std::cout << "Case #" << ++cas << ": " << ans << std::endl;
	}
	return 0;
}