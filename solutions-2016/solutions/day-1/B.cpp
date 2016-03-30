#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>

typedef unsigned long long ULL;

const int N = 2000;
const int M = (N >> 6) + 1;

struct Bitset {
    Bitset() {
        memset(bitset_, 0, sizeof(bitset_));
    }

    ULL& operator [](int index) {
        return bitset_[index];
    }

    ULL  operator [](int index) const {
        return bitset_[index];
    }

    void set(int i) {
        bitset_[i >> 6] |= 1ULL << (i & 63);
    }

    void unset(int i) {
        bitset_[i >> 6] &= ~(1ULL << (i & 63));
    }

    ULL bitset_[M];
};

char   buffer[N + 1];
int    distance[N];
Bitset graph[N], unvisited;

long long solve(int n, int s) {
    for (int i = 0; i < n; ++ i) {
        unvisited.set(i);
        distance[i] = n;
    }
    unvisited.unset(s);
    distance[s] = 0;
    std::queue<int> queue;
    queue.push(s);
    while (!queue.empty()) {
        int u = queue.front();
        queue.pop();
        for (int i = 0; i < M; ++ i) {
            ULL mask = unvisited[i] & graph[u][i];
            while (mask > 0) {
                int j = __builtin_ctzll(mask);
                mask ^= 1ULL << j;
                int v = i << 6 | j;
                distance[v] = distance[u] + 1;
                unvisited.unset(v);
                queue.push(v);
            }
        }
    }
    long long result = 0;
    for (int i = 0; i < n; ++ i) {
        result += distance[i] * distance[i];
    }
    return result;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        scanf("%s", buffer);
        for (int j = 0; j < n; ++ j) {
            if (buffer[j] == '1') {
                graph[i].set(j);
            }
        }
    }
    long long result = 0;
    for (int s = 0; s < n; ++ s) {
        result += solve(n, s);
    }
    std::cout << result << std::endl;
    return 0;
}
