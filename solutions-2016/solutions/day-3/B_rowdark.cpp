/*
	Fact: x \in [0, 100000] and 2 ^ x mod (1e9 + 7) == 0 -> x = 0
*/
#include<stdio.h>
#include<algorithm>
#include<vector>
using namespace std;

const int mod = 1000000007; // 1e9 + 7

const int MAXN = 200000, MAXM = 100;

int N, M;

int C[MAXN + 10];
int ans[MAXN + 10];
int cnt[MAXM + 10];
int W[MAXN + 10];
int Pow2[MAXN + 10], PowInv2[MAXN + 10], Pow2Minus1Inv[MAXN + 10], ChangeVal[MAXN + 10];
int toSubtract[MAXN + 10], toAdd[MAXN + 10];

inline int Pow(long long x, long long y){
	long long z = 1;
	x %= mod;
	while(y){
		if(y & 1){
			z = z * x % mod;
		}
		x = x * x % mod;
		y >>= 1;
	}
	return z;
}

inline int func(int x){
	return (((2LL * x + 3) * x + 3) % mod * x + 3) % mod;
}

pair<int, int> rec[201];
int recLen;

inline void Add(int &x, const int &y){
	x += y;
	if(x >= mod) x -= mod;
}

int main(){
	scanf("%d%d", &N, &M);
	
	Pow2[0] = PowInv2[0] = 1;
	for(int i = 1; i <= N; ++i){
		W[i] = func(i);
		Pow2[i] = Pow2[i - 1] * 2 % mod;
		PowInv2[i] = PowInv2[i - 1] * ((mod + 1LL) / 2) % mod;
		Pow2Minus1Inv[i] = Pow(Pow2[i] - 1, mod - 2);
		ChangeVal[i] = (long long)Pow2Minus1Inv[i] * Pow2[i - 1] % mod;
	}
	
	for(int i = 1; i <= N; ++i){
		scanf("%d", C + i);
		cnt[C[i]]++;
	}
	
	if(*min_element(cnt + 1, cnt + M + 1) == 0){
		printf("0\n");
		return 0;
	}
	
	long long total = 1;
	for(int i = 1; i <= M; ++i){
		total = total * (Pow2[cnt[i]] - 1) % mod;
	}
	
	for(int i = N; i > 0; --i){
		int sel = recLen + 1;
		for(int j = 1; j <= recLen; ++j){
			if(rec[j].second == C[i]){
				sel = j;
				break;
			}
		}
		for(int j = sel; j > 1; --j){
			rec[j] = rec[j - 1];
		}
		rec[1] = make_pair(i, C[i]);
		recLen = max(recLen, sel);
		long long tmp = total * ChangeVal[cnt[C[i]]] % mod;
		Add(ans[1], tmp);
		for(int j = 2; j <= recLen; ++j){
			tmp = tmp * PowInv2[rec[j].first - 1 - rec[j - 1].first] % mod;
			Add(toSubtract[rec[j].first - i + 1], tmp);
			tmp = tmp * ChangeVal[cnt[rec[j].second]] % mod;
			Add(toAdd[rec[j].first - i + 1], tmp);
		}
		tmp = tmp * PowInv2[N - rec[recLen].first] % mod;
		Add(toSubtract[N - i + 2], tmp);
	}
	
	for(int i = 2; i <= N; ++i){
		ans[i] = ((long long)(ans[i - 1] - toSubtract[i]) * PowInv2[1] + toAdd[i]) % mod;
		if(ans[i] < 0) ans[i] += mod;
	}
	
	int sum = 0;
	int sum2 = 0;
	for(int i = N; i >= 1; --i){
		Add(sum2, sum);
		ans[i] -= sum2;
		if(ans[i] < 0) ans[i] += mod;
		Add(sum, ans[i]);
		Add(sum2, ans[i]);
	}
	
	long long totalAns = 0;
	for(int i = 1; i <= N; ++i){
		totalAns = (totalAns + (long long)ans[i] * W[i]) % mod;
	}
	printf("%d\n", int(totalAns));
	return 0;
}
