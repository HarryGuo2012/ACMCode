#include <cstdio>

#define MAX_N 100005
#define inf MAX_N
int N, M, F;

int P[MAX_N], nP[MAX_N], nPsize = 0;

std::vector<int> turning;

struct node {
	int in, out;
	node(int i, int o) : in(i), out(o){}
	node(){}
};

std::vector<node> vn;

long long dp[MAX_N];

int main() {
	scanf("%d%d%d", &N, &M, &F);
	for (int i = 1; i <= N; i++)
		scanf("%d", &P[i]);
	for (int i = 1; i <= N; i++) 
		if (P[i] != nP[nPsize]) 
			nP[++nPsize] = P[i];
	nP[0] = inf;
	nP[nPsize + 1] = 0;
	for (int i = 1; i <= nPsize; i++) {
		if (nP[i] > nP[i - 1] && nP[i] > nP[i + 1])
			turning.push_back(nP[i]);
		if (nP[i] < nP[i - 1] && nP[i] < nP[i + 1]) 
			turning.push_back(nP[i]);
	}
	dp[0] = M;
	vn.push_back(node(0, 0));
	for (int i = 0; i < turning.size(); i += 2) 
		vn.push_back(turning[i], turning[i + 1]);
	for (int i = 1; i < vn.size(); i++) {
		
	}
	return 0;
}