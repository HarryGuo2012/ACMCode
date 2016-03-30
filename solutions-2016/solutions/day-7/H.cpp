#include <cstdio>
#include <cassert>
using namespace std;

double C(int n, int k) {
    int rem2 = n;
    double ans = 1;
    for (int i = k; i >= 1; i--) {
        ans = ans * (n - k + i) / i;
        while (ans > 1e9 && rem2 > 0)
            rem2--, ans /= 2;
    }
    while (rem2 > 0)
        rem2--, ans /= 2;
    assert(ans < 1.1);
    return ans;
};

inline double move_forward(double c, int n, int k) {
    return c * (n - k) / (k + 1);
}

inline double move_backward(double c, int n, int k) {
    return c * k / (n - k + 1);
}

double get_expected(int n) {
    return 1.0 / (n + 1) / (n + 1);
}

int main() {
    double w, h;
    int n;
    scanf("%lf %lf %d", &w, &h, &n);
    double ans = 0;
    int mid_k = n / 2;
    double mid_c = C(n, mid_k);
    assert(1.1 > mid_c && mid_c > 1e-9);
    int cur_k;
    double cur_c;
    
    for (cur_c = mid_c, cur_k = mid_k; cur_c > 1e-50; cur_c = move_backward(cur_c, n, cur_k), --cur_k)
        ans += get_expected(cur_k) * get_expected(n - cur_k) * cur_c;
    for (cur_c = move_forward(mid_c, n, mid_k), cur_k = mid_k + 1; cur_c > 1e-50; cur_c = move_forward(cur_c, n, cur_k), ++cur_k)
        ans += get_expected(cur_k) * get_expected(n - cur_k) * cur_c;
    printf("%.10lg\n", ans * w * h);
}
