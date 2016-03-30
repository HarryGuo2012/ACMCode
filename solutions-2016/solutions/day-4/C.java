import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.StringTokenizer;

public class Solution {
    class Pair implements Comparable <Pair> {
        Pair(int first, int second) {
            this.first = first;
            this.second = second;
        }

        @Override
        public int compareTo(Pair other) {
            return other.first - first;
        }

        int first, second;
    }

    public static void main(String[] args) {
        new Solution().run();
    }

    int timestamp;
    int[] visited, matchX, matchY, parent, via;
    List<List<Integer>> graph, rgraph;

    void link(int u, int v) {
        matchX[u] = v;
        matchY[v] = u;
    }

    boolean find(int u) {
        if (visited[u] == timestamp) {
            return false;
        }
        visited[u] = timestamp;
        for (int v : graph.get(u)) {
            if (matchY[v] == -1 || find(matchY[v])) {
                link(u, v);
                return true;
            }
        }
        return false;
    }

    void dfs(int u) {
        visited[u] = timestamp;
        for (int v : graph.get(u)) {
            int w = matchY[v];
            assert w != -1;
            if (visited[w] != timestamp) {
                parent[w] = u;
                via[w] = v;
                dfs(w);
            }
        }
    }

    void rdfs(int u) {
        visited[u] = timestamp;
        int v = matchX[u];
        if (v == -1) {
            return;
        }
        for (int w : rgraph.get(v)) {
            if (visited[w] != timestamp) {
                parent[w] = u;
                via[w] = v;
                rdfs(w);
            }
        }
    }

    public void run() {
        InputReader reader = new InputReader(System.in);
        PrintWriter writer = new PrintWriter(System.out);
        try {
            int n = reader.nextInt();
            int m = reader.nextInt();
            int q = reader.nextInt();
            int[] weight = new int[n];
            graph = new ArrayList<List<Integer>>();
            rgraph = new ArrayList<List<Integer>>();
            for (int i = 0; i < n; ++ i) {
                weight[i] = reader.nextInt();
                graph.add(new ArrayList<Integer>());
                rgraph.add(new ArrayList<Integer>());
            }
            for (int i = 0; i < m; ++ i) {
                int a = reader.nextInt() - 1;
                int b = reader.nextInt() - 1;
                graph.get(a).add(b);
                rgraph.get(b).add(a);
            }
            int result = 0;
            List<Pair> order = new ArrayList<Pair>();
            for (int i = 0; i < n; ++ i) {
                order.add(new Pair(weight[i], i));
            }
            Collections.sort(order);
            timestamp = 0;
            visited = new int[n];
            matchX = new int[n];
            matchY = new int[n];
            Arrays.fill(matchX, -1);
            Arrays.fill(matchY, -1);
            timestamp ++;
            for (Pair p : order) {
                if (p.first > 0 && find(p.second)) {
                    timestamp ++;
                    result += p.first;
                }
            }
            parent = new int[n];
            via = new int[n];
            while (q > 0) {
                q --;
                int u = reader.nextInt() - 1;
                timestamp ++;
                if (matchX[u] == -1) {
                    weight[u] = reader.nextInt();
                    if (weight[u] > 0) {
                        if (find(u)) {
                            result += weight[u];
                        } else {
                            timestamp ++;
                            dfs(u);
                            int best = u;
                            for (int w = 0; w < n; ++ w) {
                                if (visited[w] == timestamp && weight[w] < weight[best]) {
                                    best = w;
                                }
                            }
                            if (best != u) {
                                matchX[best] = -1;
                                for (int p = best; p != u; p = parent[p]) {
                                    link(parent[p], via[p]);
                                }
                                result += weight[u] - weight[best];
                            }
                        }
                    }
                } else {
                    result -= weight[u];
                    weight[u] = reader.nextInt();
                    result += weight[u];
                    rdfs(u);
                    int best = u;
                    for (int w = 0; w < n; ++ w) {
                        if (visited[w] == timestamp && matchX[w] == -1 && weight[w] > weight[best]) {
                            best = w;
                        }
                    }
                    if (weight[best] <= 0) {
                        result -= weight[u];
                        matchY[matchX[u]] = -1;
                        matchX[u] = -1;
                    } else if (best != u) {
                        for (int p = best; p != u; p = parent[p]) {
                            link(p, via[p]);
                        }
                        matchX[u] = -1;
                        result += weight[best] - weight[u];
                    }
                }
                writer.println(result);
            }
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
