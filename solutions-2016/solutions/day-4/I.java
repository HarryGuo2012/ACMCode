import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.Collections;
import java.util.List;
import java.util.StringTokenizer;

public class Solution {
    final static int INF = (int)1e9;

    public static void main(String[] args) {
        new Solution().run();
    }

    int find(int[] parent, int u) {
        if (parent[u] != u) {
            parent[u] = find(parent, parent[u]);
        }
        return parent[u];
    }

    int solve(int[][] cost, int root) {
        int n = cost.length;
        int[] parent = new int[n];
        for (int u = 0; u < n; ++ u) {
            parent[u] = u;
        }
        int answer = 0;
        while (true) {
            int[] chosen = new int[n];
            Arrays.fill(chosen, -1);
            for (int u = 0; u < n; ++ u) {
                if (find(parent, u) == u && u != find(parent, root)) {
                    for (int v = 0; v < n; ++ v) {
                        if (find(parent, v) == v && (chosen[u] == -1 || cost[v][u] < cost[chosen[u]][u])) {
                            chosen[u] = v;
                        }
                    }
                    if (chosen[u] == -1 || cost[chosen[u]][u] >= INF) {
                        return -1;
                    }
                }
            }
            boolean found = false;
            int [] visit = new int[n];
            Arrays.fill(visit, -1);
            for (int u = 0; u < n && !found; ++ u) {
                if (chosen[u] != -1 && visit[u] == -1) {
                    int v = u;
                    ArrayList <Integer> stack = new ArrayList <Integer>();
                    while (chosen[v] != -1 && visit[v] == -1) {
                        stack.add(v);
                        visit[v] = u;
                        v = chosen[v];
                    }
                    if (chosen[v] != -1 && visit[v] == u) {
                        found = true;
                        ArrayList <Integer> cycle = new ArrayList <Integer>();
                        for (int i = stack.size() - 1; i >= 0; -- i) {
                            int p = stack.get(i);
                            answer += cost[chosen[p]][p];
                            cycle.add(p);
                            if (p == v) {
                                break;
                            }
                        }
                        for (int p : cycle) {
                            parent[p] = v;
                        }
                        for (int p = 0; p < n; ++ p) {
                            if (find(parent, p) == p && find(parent, p) != v) {
                                int tmp = INF;
                                for (int q : cycle) {
                                    if (cost[p][q] < INF) {
                                        tmp = Math.min(tmp, cost[p][q] - cost[chosen[q]][q]);
                                    }
                                    cost[v][p] = Math.min(cost[v][p], cost[q][p]);
                                }
                                cost[p][v] = tmp;
                            }
                        }
                        cost[v][v] = INF;
                    }
                }
            }
            if (!found) {
                for (int u = 0; u < n; ++ u) {
                    if (chosen[u] != -1) {
                        answer += cost[chosen[u]][u];
                    }
                }
                break;
            }
        }
        return answer;
    }

    public void run() {
        InputReader reader = new InputReader(System.in);
        PrintWriter writer = new PrintWriter(System.out);
        try {
            int n = reader.nextInt();
            int[] destination = new int[n];
            for (int i = 0; i < n; ++ i) {
                destination[i] = reader.nextInt() - 1;
            }
            int[][] distance = new int[n][n];
            for (int i = 0; i < n; ++ i) {
                Arrays.fill(distance[i], n);
                distance[i][i] = 0;
            }
            for (int i = 0; i < n - 1; ++ i) {
                int a = reader.nextInt() - 1;
                int b = reader.nextInt() - 1;
                distance[a][b] = distance[b][a] = 1;
            }
            for (int k = 0; k < n; ++ k) {
                for (int i = 0; i < n; ++ i) {
                    for (int j = 0; j < n; ++ j) {
                        distance[i][j] = Math.min(distance[i][j], distance[i][k] + distance[k][j]);
                    }
                }
            }
            List<List<Integer>> cycles = new ArrayList<List<Integer>>();
            if (true) {
                List<Integer> cycle = new ArrayList<Integer>();
                cycle.add(0);
                cycles.add(cycle);
            }
            int required = 0;
            if (true) {
                boolean[] visited = new boolean[n];
                for (int i = 0; i < n; ++ i) {
                    if (destination[i] != i && !visited[i]) {
                        List<Integer> cycle = new ArrayList<Integer>();
                        for (int j = i; !visited[j]; j = destination[j]) {
                            visited[j] = true;
                            cycle.add(j);
                            required += distance[j][destination[j]];
                        }
                        cycles.add(cycle);
                    }
                }
            }
            int m = cycles.size();
            int[][] mergedDistance = new int[m][n];
            for (int i = 0; i < m; ++ i) {
                Arrays.fill(mergedDistance[i], n);
                for (int v : cycles.get(i)) {
                    for (int j = 0; j < n; ++ j) {
                        mergedDistance[i][j] = Math.min(mergedDistance[i][j], distance[0][v] + distance[v][j] - distance[0][j] >> 1);
                    }
                }
            }
            int[] parent = new int[n];
            for (int i = 1; i < n; ++ i) {
                while (distance[0][parent[i]] + 1 != distance[0][i] || distance[parent[i]][i] != 1) {
                    parent[i] ++;
                }
            }
            int[][] graph = new int[m][m];
            for (int i = 0; i < m; ++ i) {
                List<Integer> cycle = cycles.get(i);
                Collections.sort(cycle, new Comparator<Integer>() {
                    @Override
                    public int compare(Integer i, Integer j) {
                        return distance[0][j] - distance[0][i];
                    }
                });
                int head = 0;
                int tail = 0;
                int[] queue = new int[n];
                boolean[] visited = new boolean[n];
                for (int v : cycle) {
                    visited[queue[tail ++] = v] = true;
                }
                while (tail - head > 1) {
                    int backup = head;
                    while (distance[0][queue[backup]] == distance[0][queue[head]]) {
                        head ++;
                    }
                    for (int j = head - 1; j >= backup; -- j) {
                        int p = parent[queue[j]];
                        if (!visited[p]) {
                            visited[p] = true;
                            queue[-- head] = p;
                        }
                    }
                }
                Arrays.fill(graph[i], n);
                for (int j = 0; j < n; ++ j) {
                    if (visited[j]) {
                        for (int k = 0; k < m; ++ k) {
                            graph[i][k] = Math.min(graph[i][k], mergedDistance[k][j]);
                        }
                    }
                }
            }
            writer.println(required + solve(graph, 0) * 2);
        } catch (IOException e) {
        } finally {
            writer.close();
        }
    }

    class InputReader {
        InputReader(InputStream in) {
            this.reader    = new BufferedReader(new InputStreamReader(in));
            this.tokenizer = new StringTokenizer("");
        }

        public String nextToken() throws IOException {
            while (!tokenizer.hasMoreTokens()) {
                tokenizer = new StringTokenizer(reader.readLine());
            }
            return tokenizer.nextToken();
        }

        public int nextInt() throws IOException {
            return Integer.parseInt(nextToken());
        }

        private BufferedReader  reader;
        private StringTokenizer tokenizer;
    }

    private void debug(Object...o) {
        System.err.println(Arrays.deepToString(o));
    }
}
