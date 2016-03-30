#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <bitset>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

#ifdef _WIN32
#  define LN 2
#else
#  define LN 1
#endif

const int N = 6000;

typedef bitset<2*N+6> T;

int header, n, row;
char buf[N+1];

void get( int i, T &save ) {
  fseek(stdin, header + i * (row + LN), SEEK_SET);
  fread(buf, 1, row, stdin);
  buf[row] = 0;
  int k = 0;
  forn(j, row) 
    forn(t, 6)
      save[k++] = ((buf[j] - 33) >> t) & 1;
}

int main() {
  fread(buf, 1, sizeof(buf), stdin);
  sscanf(buf, "%d", &n);
  sprintf(buf, "%d", n);
  header = strlen(buf) + LN;
  row = (2 * n + 5) / 6;
  assert(n <= N);

  T a, b;
  int m = n + 1;
  while (1) {
    int i = rand() % m;
    int j = rand() % m;
    if (i == j)
      continue;
    get(i, a);
    get(j, b);
    if (2 * (int)(a & b).count() >= n) {
      printf("%d %d\n", j + 1, i + 1);
      return 0;
    }
  }
  return 0;
}
