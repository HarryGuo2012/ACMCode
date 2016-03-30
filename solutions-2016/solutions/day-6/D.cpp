#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

inline int readInt(); 

int main() {
	int n = readInt();
	pair<int, int> a[n];
	forn(i, n) a[i].first = readInt();
	forn(i, n) a[i].second = readInt();

	sort(a, a + n, greater<pair<int,int>>());

	multiset <int> s;
	forn(i, n)
		if (s.size() < (i + 1) / 2)
			s.insert(a[i].second);
		else if (s.size() && *s.begin() < a[i].second)
			s.erase(s.begin()), s.insert(a[i].second);

	cout << accumulate(s.begin(), s.end(), 0LL) << endl;
	return 0;
}

/** Read */

static const int buf_size = 4096;

inline int getChar() {
	static char buf[buf_size];
	static int len = 0, pos = 0;
	if (pos == len)
		pos = 0, len = fread(buf, 1, buf_size, stdin);
	if (pos == len)
		return -1;
	return buf[pos++];
}

inline int readChar() {
	int c = getChar();
	while (c <= 32)
		c = getChar();
	return c;
}

inline int readInt() {
	int x = 0, s = 1, c = readChar();
	if (c == '-')
		s = -1, c = getChar();
	while ('0' <= c && c <= '9')
		x = x * 10 + c - '0', c = getChar();
	return s == 1 ? x : -x;
}
