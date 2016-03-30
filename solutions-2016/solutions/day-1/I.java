import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.StringTokenizer;

public class Solution {
    public static void main(String[] args) {
        new Solution().run();
    }

    static int MOD = (int)1e9 + 7;

    void multiply(int[] a, int[] b, int[] c, int i) {
        for (int subset = (1 << i) - 1; subset >= 0; -- subset) {
            if (a[subset] > 0) {
                int rest = (1 << i) - 1 ^ subset;
                for (int subset2 = rest;; subset2 = subset2 - 1 & rest) {
                    int union = subset ^ subset2 ^ 1 << i;
                    c[union] += (int)((long)a[subset] * b[subset2] % MOD);
                    if (c[union] >= MOD) {
                        c[union] -= MOD;
                    }
                    if (subset2 == 0) {
                        break;
                    }
                }
            }
        }
    }


    int solve(int n, int d, int[][][] graph) {
        if ((n & 1) == 1) {
            return 0;
        }
        int[] result = new int[1 << d];
        result[0] = 1;
        for (int i = 0; i < n >> 1; ++ i) {
            int x = n - (i + 1 << 1);
            int y = x + 1;
            multiply(result, graph[x][y], result, i);
            for (int j = 0; j < x; ++ j) {
                for (int k = j + 1; k < x; ++ k) {
                    multiply(graph[j][x], graph[k][y], graph[j][k], i);
                    multiply(graph[j][y], graph[k][x], graph[j][k], i);
                }
            }
        }
        return result[(1 << d) - 1];
    }

    public void run() {
        InputReader reader = new InputReader(System.in);
        try {
            int n = reader.nextInt();
            int m = reader.nextInt();
            int d = n >> 1;
            int[][][] graph = new int[n][n][1 << d];
            for (int i = 0; i < m; ++ i) {
                int a = reader.nextInt() - 1;
                int b = reader.nextInt() - 1;
                if (a < b) {
                    graph[a][b][0] ++;
                } else {
                    graph[b][a][0] ++;
                }
            }
            PrintWriter writer = new PrintWriter(System.out);
            writer.println(solve(n, d, graph));
            writer.close();
        } catch (IOException e) {
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
