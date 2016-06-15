#include <cstdio>
#include <map>
#include <set>
#include <vector>
#include <algorithm>

int n;

typedef std::pair<int, int> P;

P operator- (P a, P b) {
    return std::make_pair(a.first - b.first, a.second - b.second);
}

P operator+ (P a, P b) {
    return std::make_pair(a.first + b.first, a.second + b.second);
}

#define MAX_N 2004 * 2004

std::set<P> se;
std::vector<P> cnt;
std::vector<P> tmpInter;
std::map<int, int> X;
std::vector<P> vectorsOfIntercept[MAX_N];
std::vector<P> vectorsOfX[MAX_N];

std::pair<P, bool> getIntercept (P u, P v) {
    if (u.first == v.first) return std::make_pair(std::make_pair(0, 0), 0); 
    int dy = u.second - v.second, dx = u.first - v.first;
    int a = -dy * u.first + dx * u.second, b = dx;
    int g = std::__gcd(abs(a), abs(b));
    return std::make_pair(std::make_pair(a / g, b / g), 1);
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        if (se.find(std::make_pair(x, y)) != se.end()) continue;
        se.insert(std::make_pair(x, y));
    }

    int tot = 0, xtot = 0;

    for (auto u : se)
        for(auto v : se) {
            if (u == v) continue;
            auto p = getIntercept(u, v);
            if(p.second)
                tmpInter.push_back(p.first);
        }

    std::sort(tmpInter.begin(), tmpInter.end());
    auto it = std::unique(tmpInter.begin(), tmpInter.end());
    tmpInter.resize(std::distance(tmpInter.begin(), it));

    for (auto u : se)
        for (auto v : se) {
            if (u == v) continue;
            auto p = getIntercept(u, v);
            //printf("(%d %d),(%d %d),(%d %d)\n", u.first, u.second, v.first, v.second, p.first.first, p.first.second);
            auto t = u - v;
            if (p.second) {
                int pos = std::lower_bound(tmpInter.begin(), tmpInter.end(), p.first) - tmpInter.begin();
                vectorsOfIntercept[pos].push_back(t);
            }
            else {
                if(X.find(u.first) == X.end()) X[u.first] = xtot++;
                vectorsOfX[X[u.first]].push_back(t);
            }
            cnt.push_back(t);
        }

    std::sort(cnt.begin(), cnt.end());

    long long ans = 0;
    for (int i = 0; i < cnt.size(); i++) {
        if (i > 0 && cnt[i] == cnt[i - 1]) continue;
        auto it = std::equal_range(cnt.begin(), cnt.end(), cnt[i]);
        long long tmp = it.second - it.first;
        ans = ans + tmp * (tmp - 1) / 2;
    }

    long long zeroArea = 0;
    for (int i = 0; i < tmpInter.size(); i++) {
        std::sort(vectorsOfIntercept[i].begin(), vectorsOfIntercept[i].end());
        for (int j = 0; j < vectorsOfIntercept[i].size(); j++) {
            if(j > 0 && vectorsOfIntercept[i][j] == vectorsOfIntercept[i][j - 1]) continue;
            auto it = std::equal_range(vectorsOfIntercept[i].begin(), vectorsOfIntercept[i].end(), vectorsOfIntercept[i][j]);
            long long tmp = it.second - it.first;
            zeroArea = zeroArea + tmp * (tmp - 1) / 2;
        }
    }

    //printf("%lld\n", zeroArea);
            
    for (int i = 0; i < xtot; i++) {
        std::sort(vectorsOfX[i].begin(), vectorsOfX[i].end());
        for (int j = 0; j < vectorsOfX[i].size(); j++) {
            if(j > 0 && vectorsOfX[i][j] == vectorsOfX[i][j - 1]) continue;
            auto it = std::equal_range(vectorsOfX[i].begin(), vectorsOfX[i].end(), vectorsOfX[i][j]);
            long long tmp = it.second - it.first;
            zeroArea = zeroArea + tmp * (tmp - 1) / 2;
        }
    }
        
    ans -= zeroArea;
    ans /= 4;

    printf("%lld\n", ans);
    return 0;
}