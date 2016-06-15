#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
using namespace std;

vector<int> G[100];

int b[100];
int n;
void dfs(int u, int s) {
	int i = 0;
	while((s >> i & 1) == 0) i = rand() % n + 1;
	b[u] = i;
	for (auto v : G[u])
		dfs(v, s | (1 << v));
}

int main() {
	srand(time(0));
	n = rand() % 10 + 1;
	cout << n << " " << n - 1 << endl;
	for (int i = 2; i <= n; i++) {
		int t = rand() % (i - 1) + 1;
		G[t].push_back(i);
		cout << t << " " << i << endl;
	}
	dfs(1, 2);
	for (int i = 1; i <= n; i++)
		cout << b[i] << endl;
	return 0;
}