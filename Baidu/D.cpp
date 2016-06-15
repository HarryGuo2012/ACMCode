#include <cstdio>
#include <algorithm>
#include <string>
#include <map>
#include <cstring>

#define MAX_A 44

int N;
char buff[MAX_A];
std::string s;
std::map<std::string, int> ma;
int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%s", buff);
		std::sort(buff, buff + strlen(buff));
		s = buff;
		printf("%d\n", ma[s]);
		ma[s]++;
	}
	return 0;
}