#include <cstdio>
#include <vector>
#include <algorithm>

int n;

std::vector<int> a, b, c;
int ans[1111];

int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		int t;
		scanf("%d", &t);
		a.push_back(t);
	}
	std::sort(a.begin(),a.end());
	int tmp = n / 2 + n % 2;
	for(int i = 0; i < tmp; i++)
		b.push_back(a[i]);
	for(int i = tmp; i < a.size(); i++)
		c.push_back(a[i]);
	for(int i = 0; i < b.size(); i++)
		ans[2 * i] = b[i];
	for(int i = 0; i < c.size(); i++)
		ans[2 * i + 1] = c[i];
	for(int i = 0; i < n; i++){
		if(i & 1)
			if(ans[i] < ans[i - 1]){
				printf("Impossible\n");
				return 0;
			}
		if(i > 0 && (i & 1) == 0)
			if(ans[i] > ans[i - 1]){
				printf("Impossible\n");
				return 0;
			}
	}
	for(int i = 0; i < n; i++)
		printf("%d ", ans[i]);
	printf("\n");
	return 0;
}