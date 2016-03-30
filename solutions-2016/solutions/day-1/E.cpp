#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <utility>
#include <vector>

#define ALL(v) (v).begin(), (v).end()

typedef long double Double;
typedef long long   Long;

struct Point {
    Point(Double x = 0., Double y = 0.) : x(x), y(y) {}

    Double x, y;
};

const int    N   = 200000;
const Double INF = 1e100;
const Double EPS = 1e-11;

int signum(double x) {
    return x < -EPS ? -1 : x > EPS;
}

bool operator < (const Point &a, const Point &b) {
    if (signum(a.x - b.x) != 0) {
        return a.x < b.x;
    }
    return a.y < b.y;
}

bool operator == (const Point &a, const Point &b) {
    return signum(a.x - b.x) == 0 && signum(a.y - b.y) == 0;
}

Point operator - (const Point &a, const Point &b) {
    return Point(a.x - b.x, a.y - b.y);
}

double det(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}

bool check(const Point &a, const Point &b, const Point &c) {
    return det(b - a, c - b) > 0;
}

int  a[N], b[N], c[N];
bool removed[N];

Double slope(int i) {
    return b[i] ? (Double)a[i] / b[i] : INF;
}

bool by_k(int i, int j) {
    return slope(i) < slope(j);
}

Point intersect(int i, int j) {
    Double d = (Long)a[i] * b[j] - (Long)a[j] * b[i];
    return Point( ((Long)b[j] * c[i] - (Long)b[i] * c[j]) / d
                , ((Long)a[i] * c[j] - (Long)a[j] * c[i]) / d
                );
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++ i) {
        scanf("%d%d%d", a + i, b + i, c + i);
    }
    memset(removed, 0, sizeof(*removed) * n);
    std::vector<std::pair<int, int>> removed_pairs;
    for (int _ = 0; _ < m; ++ _) {
        int x, y;
        scanf("%d%d", &x, &y);
        x --;
        y --;
        removed[x] = removed[y] = true;
        removed_pairs.push_back({x, y});
        removed_pairs.push_back({y, x});
    }
    std::vector<int> order;
    for (int i = 0; i < n; ++ i) {
        if (!removed[i]) {
            order.push_back(i);
        }
    }
    std::vector<Point> points;
    if (true) {
        int n = order.size();
        std::sort(ALL(order), by_k);
        for (int i = 0; i < n; ++ i) {
            int j = (i + 1) % n;
            if (i != j) {
                points.push_back(intersect(order[i], order[j]));
            }
        }
    }
    std::sort(ALL(removed_pairs));
    for (int i = 0, t = 0; i < n; ++ i) {
        if (removed[i]) {
            Point min_p(INF, INF), max_p(-INF, -INF);
            for (int j = 0; j < n; ++ j) {
                std::pair<int, int> p(i, j);
                while (t < (int)removed_pairs.size() && removed_pairs[t] < p) {
                    t ++;
                }
                if (i != j && (t == (int)removed_pairs.size() || p < removed_pairs[t])) {
                    Point p = intersect(i, j);
                    min_p = std::min(min_p, p);
                    max_p = std::max(max_p, p);
                }
            }
            if (min_p.x < INF) {
                points.push_back(min_p);
                points.push_back(max_p);
            }
        }
    }
    double result = 0.;
    if (!points.empty()) {
        std::sort(ALL(points));
        points.erase(std::unique(ALL(points)), points.end());
        std::vector<Point> hull;
        for (const Point &p : points) {
            while ((int)hull.size() > 1 && !check(hull[(int)hull.size() - 2], hull.back(), p)) {
                hull.pop_back();
            }
            hull.push_back(p);
        }
        points.pop_back();
        std::reverse(ALL(points));
        int h = hull.size();
        for (const Point &p : points) {
            while ((int)hull.size() > h && !check(hull[(int)hull.size() - 2], hull.back(), p)) {
                hull.pop_back();
            }
            hull.push_back(p);
        }
        for (int i = 1; i < (int)hull.size(); ++ i) {
            const Point &p = hull[i];
            const Point &q = hull[i - 1];
            result += hypot(p.x - q.x, p.y - q.y);
        }
    }
    printf("%.10f\n", result);
    return 0;
}
