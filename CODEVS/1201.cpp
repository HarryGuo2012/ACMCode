#include <iostream>
#include <algorithm>
using namespace std;

int n;
long long minNum = ((long long)1 << 40) + 100;
long long maxNum = -((long long)1 << 40) + 100;

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		long long a;
		cin >> a;
		minNum = min(a, minNum);
		maxNum = max(a, maxNum);
	}
	cout << minNum << " " << maxNum << endl;
	return 0;
}