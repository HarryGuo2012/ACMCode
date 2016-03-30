import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.List;
import java.util.ArrayList;
import java.util.StringTokenizer;

public class Solution {
    public static void main(String[] args) {
        new Solution().run();
    }

    static int MOD = (int)1e9 + 7;

    class Pair {
        Pair(int i, int j) {
            this.i = i;
            this.j = j;
        }

        Pair shift(int d) {
            return new Pair(i + d, j + d);
        }

        int i, j;
    }

    int[] parent;

    int find(int u) {
        if (parent[u] != u) {
            parent[u] = find(parent[u]);
        }
        return parent[u];
    }

    boolean merge(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) {
            return false;
        }
        parent[u] = v;
        return true;
    }

    public void run() {
        InputReader reader = new InputReader(System.in);
        PrintWriter writer = new PrintWriter(System.out);
        try {
            while (true) {
                int n = reader.nextInt();
                int m = reader.nextInt();
                int[] log = new int[n + 1];
                log[1] = 0;
                for (int i = 1; i <= n; ++ i) {
                    log[i] = log[i - 1];
                    if (1 << log[i] + 1 < i) {
                        log[i] ++;
                    }
                }
                List<List<Pair>> pairs = new ArrayList<List<Pair>>();
                for (int i = 0; i <= log[n]; ++ i) {
                    pairs.add(new ArrayList<Pair>());
                }
                for (int i = 0; i < m; ++ i) {
                    int a = reader.nextInt() - 1;
                    int b = reader.nextInt() - 1;
                    int c = reader.nextInt();
                    int l = log[c];
                    pairs.get(l).add(new Pair(a, b));
                    int d = c - (1 << l);
                    pairs.get(l).add(new Pair(a + d, b + d));
                }
                for (int l = log[n]; l >= 0; -- l) {
                    parent = new int[n];
                    for (int i = 0; i < n; ++ i) {
                        parent[i] = i;
                    }
                    for (Pair p : pairs.get(l)) {
                        if (merge(p.i, p.j) && l > 0) {
                            pairs.get(l - 1).add(p);
                            pairs.get(l - 1).add(p.shift(1 << l - 1));
                        }
                    }
                }
                long result = 1;
                for (int i = 0; i < n; ++ i) {
                    if (parent[i] == i) {
                        result *= 26;
                        result %= MOD;
                    }
                }
                writer.println(result);
            }
        } catch (Exception e) {
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
