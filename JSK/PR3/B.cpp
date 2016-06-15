#include <string>
#include <iostream>

using std::string;
using std::cin;
using std::cout;
using std::endl;

string s;

#define MAX_N 55

int N;

int a[MAX_N][MAX_N];

int main() {
	cin >> s;
	for (int i = 0; i < s.length(); i++)
		for (int j = i; j < s.length(); j++) {
			for (int k = 1; k <= (j - i + 1); k++) {
				if ((j - i + 1) % k != 0) continue;
				if (i + k > s.length()) break;
				bool flag = true;
				for (int t = 0; t < (j - i + 1) / k; t++) {
					string u, v;
					u.assign(s.begin() + i, s.begin() + i + k);
					v.assign(s.begin() + i + k * t, s.begin() + i + k * (t + 1));
					if (u != v) {
						flag = false;
						break;
					}
				}
				if (flag) {
					a[i][j] = (j - i + 1) / k;
					break;
				}
			}
		}
	int ans = 0;
	for (int i = 0; i < s.length(); i++)
		for (int j = i; j < s.length(); j++)
			for (int x = j + 1; x < s.length(); x++)
				for (int y = x; y < s.length(); y++)
					if (a[i][j] == a[x][y])
						ans++;
	cout << ans << endl;
	return 0;
}