#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <utility>
#include <cstdlib>
#include <memory>
#include <queue>
#include <cassert>
#include <cmath>
#include <ctime>
#include <complex>
#include <bitset>

using namespace std;

#define pb push_back
#define fst first
#define snd second
#define mp make_pair
#define sz(C) ((int) (C).size())
#define forn(i, n) for (int i = 0; i < (int) n; ++i)
#define ford(i, n) for (int i = ((int) n) - 1; i >= 0; --i)
#define y1 gftxdtrtfhyjfctrxujkvbhyjice
#define y0 ehfoiuvhefroerferjhfjkehfjke
#define left sdhfsjkshdjkfsdfgkqqweqweh
#define right yytrwtretywretwreytwreytwr
#define next jskdfksdhfjkdsjksdjkgf
#define prev koeuigrihjdkjdfj
#define hash kjfdkljkdhgjdkfhgurehg
#define all(C) begin(C), end(C)
#define eprintf(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef pair <int,int> pii;
typedef pair <ll, ll> pll;
typedef vector <ll> vll;
typedef vector <int> vi;
typedef vector <vector <int> > vvi;
typedef vector <pii> vii;
typedef long double ld;
typedef complex<double> cd;
typedef vector<cd> vcd;

#define FILE_NAME "text"

const ld EPS = 1e-9;
const int INF = (int) 1.01e9;

ll gcd(ll a, ll b) {
  return b ? gcd(b, a % b) : a;
}

struct Point {
  ll x, y, z;

  Point() {}

  Point(ll x, ll y, ll z) : x(x), y(y), z(z) {}

  bool read() {
    if (cin >> x >> y >> z) {
      return 1;
    }
    return 0;
  }

  Point& operator += (const Point& p) {
    x += p.x;
    y += p.y;
    z += p.z;
    return *this;
  }

  Point operator + (const Point& p) const {
    return Point(*this) += p;
  }

  Point& operator -= (const Point& p) {
    x -= p.x;
    y -= p.y;
    z -= p.z;
    return *this;
  }

  Point operator - (const Point& p) const {
    return Point(*this) -= p;
  }

  ll operator * (const Point& p) const {
    return x * p.x + y * p.y + z * p.z;
  }

  Point operator % (const Point& p) const {
    return Point(y * p.z - p.y * z,
                 z * p.x - p.z * x,
                 x * p.y - p.x * y);
  }

  Point operator -() const {
    return Point(0, 0, 0) -= *this;
  }

  void normalize() {
    ll g = gcd(abs(x), gcd(abs(y), abs(z)));
    if  (g > 1) {
      x /= g;
      y /= g;
      z /= g;
    }
    if  (x < 0 || (x == 0 && (y < 0 || (y == 0 && z < 0)))) {
      x = -x;
      y = -y;
      z = -z;
    }
  }

  bool operator == (const Point& p) const {
    return x == p.x && y == p.y && z == p.z;
  }

  bool operator != (const Point& p) const {
    return !(*this == p);
  }

  void print() const {
    cout << x << " " << y << " " << z << '\n';
  }

  Point operator * (ll c) {
    return Point(x * c, y * c, z * c);
  }
};

struct point
{
    double x;
    double y;
    double z;
};
point operator + (const point &left, const point &right)
{
    return point{left.x + right.x, left.y + right.y, left.z + right.z};
}
point operator - (const point &left, const point &right)
{
    return point{left.x - right.x, left.y - right.y, left.z - right.z};
}
point operator % (const point &left, const point &right)
{
    return point{left.y * right.z - left.z * right.y,
                left.z * right.x - left.x * right.z,
                left.x * right.y - left.y * right.x};
}
double operator * (const point &left, const point &right)
{
    return left.x * right.x + left.y * right.y + left.z * right.z;
}
double length (const point &cur)
{
    return sqrt(cur * cur);
}
point norm (const point &cur)
{
    double Len = length(cur);
    assert(Len != 0);
    return point{cur.x / Len, cur.y / Len, cur.z / Len};
}
point mult (const point &left, double d)
{
    return point{left.x * d, left.y * d, left.z * d};
}

vector<Point> points;
int n, k;

bool read() {
  if  (scanf("%d%d", &n, &k) < 2) {
    return false;
  }
  points.resize(n);
  forn(i, n) {
    if  (!points[i].read()) {
      return false;
    }
  }
  return true;
}

struct Plane {
  Point norm;
  int id1, id2;

  Plane() {}

  Plane(int id1, int id2) : id1(id1), id2(id2) {
    norm = points[id1] - points[id2];
    norm.normalize();
  }

  Plane(Point norm) : norm(norm), id1(-1), id2(-1) {}

  bool operator < (const Plane& p) const {
    if  (norm.x != p.norm.x) {
      return norm.x < p.norm.x;
    }
    if  (norm.y != p.norm.y) {
      return norm.y < p.norm.y;
    }
    return norm.z < p.norm.z;
  }
};

vector<Plane> planes;

struct pointComp {
  static Point vect;
  static int direction;
  static Point Norm;

  inline bool operator () (const int a, const int b) {
    ll A = points[a] * vect;
    ll B = points[b] * vect;
    if  (A != B) {
      return A > B;
    }
    ll diff = (points[a] * Norm) - (points[b] * Norm);
    return direction ? diff > 0 : diff < 0;
  }
};
Point pointComp::vect, pointComp::Norm;
int pointComp::direction;

void solve() {
  points.clear();
  planes.clear();

  assert(read());

  forn(i, n) {
    for (int j = i + 1; j < n; ++j) {
      if  ((points[i] % points[j]) != Point(0, 0, 0)) {
        planes.pb(Plane(i, j));
      }
    }
  }

  planes.pb(Plane(Point(0, 0, 1)));
  planes.pb(Plane(Point(0, 1, 0)));
  planes.pb(Plane(Point(1, 0, 0)));
  sort(all(planes));

  ll res = -1;
  vi ans;

  vector<double> value(n);
  vector<int> sorted_pts(n);
  iota(sorted_pts.begin(), sorted_pts.end(), 0);

  mt19937 rng;
  uniform_real_distribution<double> dirt(0, 1e-6);
  const point walk{dirt(rng), dirt(rng), dirt(rng)};

  for (int i = 0; i < sz(planes); ) {
    int i0 = i;
    while (i < sz(planes) && !(planes[i0] < planes[i])) {
      ++i;
    }

    Point norm0 = planes[i0].norm;

    // [i0, i)
    vi sign(sz(planes), 1);
    vi to_sort; // points on circle
    forn(j, sz(planes)) {
      if  (i0 <= j && j < i) {
        continue;
      }
      Point p = planes[j].norm % norm0;
      if  (p.x < 0 || p.y < 0 || p.z < 0) {
        p = -p;
        sign[j] = -1;
      }
      if  (p.x < 0 || p.y < 0 || p.z < 0) {
        continue;
      }
      to_sort.pb(j);
    }

    if (to_sort.empty())
        continue;

    auto compInter = [&](int a, int b) { return (planes[b].norm * (planes[a].norm % planes[i0].norm)) * sign[a] * sign[b] > 0;  };
    sort(all(to_sort), compInter);
    to_sort.pb(to_sort[0]);

    for (int j = 0; j < sz(to_sort) - 1; j++)
    {
        const int cur_num = to_sort[j];
        const int next_num = to_sort[j + 1];
        if (cur_num > next_num)
            continue;
        Point A = planes[cur_num].norm % norm0;
        Point B = planes[cur_num].norm % norm0;
        if (A.x < 0)
            A = -A;
        if (B.x < 0)
            B = -B;

        point a{A.x, A.y, A.z};
        point b{B.x, B.y, B.z};
        a = norm(a); b = norm(b);

        const point middle{(A.x + B.x) / 2.0, (A.y + B.y) / 2.0, (A.z + B.z) / 2.0};

        for (int dir = -1; dir <= 1; dir += 2)
        {
            const point cur_proec = middle + mult(walk, dir);
            for (int k = 0; k < n; k++)
                value[k] = cur_proec * point{points[k].x, points[k].y, points[k].z};
            nth_element(sorted_pts.begin(), sorted_pts.begin() + k,
                        sorted_pts.end(), [&] (int x, int y)
                        {
                            return value[x] > value[y];
                        });

            Point sum_k(0, 0, 0);
            forn(v, k) sum_k += points[sorted_pts[v]];
            ll cur_res = sum_k * sum_k;
            if  (cur_res > res) {
              res = cur_res;
              ans = vi(sorted_pts.begin(), sorted_pts.begin() + k);
            }
        }
    }
  }

  sort(all(ans));
  cout << res << '\n';
  assert(sz(ans) == k);
  forn(i, k) {
    printf("%d%c", ans[i] + 1, " \n"[i + 1 == k]);
  }
}

int main() {
  int T;
  cin >> T;
  while (T --> 0) {
    solve();
  }

  return 0;
}
