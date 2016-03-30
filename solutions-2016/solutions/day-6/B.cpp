#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef double ld;

const int MAXN = 1e5 + 3;
typedef long long ll;
const ld eps = 1e-9;

struct pt {
	int x,y;
	ld real_y;
} P[MAXN];
int n, fen[MAXN];

int sum(int r) {
	int ans = 0;
	for (r++; r > 0; r &= r-1)
		ans += fen[r];
	return ans;
}

void inc(int i) {
	for (i++; i <= n; i += -i & i)
		fen[i]++;
}

inline bool ls(int a, int b) {
	return P[a].y == P[b].y ? P[a].x < P[b].x : P[a].real_y < P[b].real_y;
}

void calc_realy( ld x ) {
	forn(i, n)
		P[i].real_y = P[i].y * x + P[i].x;
}

int infp[MAXN];
int xp[MAXN];
int tmp[MAXN], tmp2[MAXN];

void inverse(int* perm, int* res) {
	forn(i, n)
		res[perm[i]] = i;
}

void multiply(int* a, int* b, int* res) {
	forn(i, n)
		res[i] = b[a[i]];
}

ll count_inversions(int* perm) {
	ll ans = 0;
	memset(fen, 0, sizeof(fen));
	forn(i, n) {
		ans += sum(perm[i]-1);
		inc(perm[i]);
	}
	return (ll)n * (n-1) / 2 - ans;
}

ll get_inv(ld x) {
	calc_realy(x); // O(n)
	sort(xp, xp + n, ls); // O(nlogn)
	multiply(xp, tmp, tmp2); // O(n)
	return count_inversions(tmp2); // O(nlogn)
}

ld find_kth(ll k1, ll k2) { // O(nlognlogM)
	assert(k1 <= k2 && k1 + 1 >= k2);
	forn(i, n)
		xp[i] = i;
	ld rb = 1e9, lb = -rb;
	calc_realy(2e10);
	sort(xp, xp + n, ls);
	inverse(xp, tmp);
	forn(it, 62) {
		ld mid = (lb + rb) * 0.5;
		if (get_inv(mid) >= k2)
			lb = mid;
		else
			rb = mid;
	}
	ld r1 = lb, r2 = lb, eps = 0.5e-9;
	if (k1 != k2 && get_inv(lb + eps) == k1) { // O(nlogn)
		calc_realy(lb + eps);
		sort(xp, xp + n, ls); 
		r2 = 1e20;
		forn(i, n - 1) {
			int a = xp[i], b = xp[i + 1];
			ld x = (ld)(P[b].x - P[a].x) / (P[a].y - P[b].y);
			if (x > lb + eps)
				r2 = min(r2, x);
		}
	}
	#define F(x) (acos(-1.)/2. - atanl(-x))
	return (F(r1) + F(r2)) * 0.5;
}

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);
	cin >> n;
	forn(i, n)
		cin >> P[i].x >> P[i].y;
	ll mid = (ll)n * (n-1) / 2; 
	printf("%.15f\n", find_kth(mid/2+(mid&1),mid/2+1));
}
