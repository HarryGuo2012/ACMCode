import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.StringTokenizer;

public class Solution {
    final static int MOD = 2017;

    public static void main(String[] args) {
        new Solution().run();
    }

    static int[][] binomTable;

    static {
        binomTable = new int[MOD][MOD];
        for (int i = 0; i < MOD; ++ i) {
            binomTable[i][0] = 1;
            for (int j = 1; j <= i; ++ j) {
                binomTable[i][j] = (binomTable[i - 1][j - 1] + binomTable[i - 1][j]) % MOD;
            }
        }
    }

    int binom(int n, int k) {
        if (n == 0 && k == 0) {
            return 1;
        }
        return (int)((long)binom(n / MOD, k / MOD) * binomTable[n % MOD][k % MOD] % MOD);
    }


    public void run() {
        InputReader reader = new InputReader(System.in);
        PrintWriter writer = new PrintWriter(System.out);
        try {
            int n   = reader.nextInt();
            int[] a = new int[n + 1];
            for (int i = 0; i < n; ++ i) {
                a[i] = reader.nextInt();
            }
            a[n] = a[n - 1];
            for (int i = n - 1; i >= 0; -- i) {
                a[i] = Math.min(a[i], a[i + 1]);
            }
            int[] ways = new int[n + 1];
            ways[0] = 1;
            for (int i = 1; i <= n; ++ i) {
                ways[i] = binom(i + a[i] + 1, i);
                for (int j = 0; j < i; ++ j) {
                    if (a[j] <= a[i]) {
                        ways[i] -= (int)((long)ways[j] * binom(i - j + a[i] - a[j], i - j) % MOD);
                        if (ways[i] < 0) {
                            ways[i] += MOD;
                        }
                    }
                }
            }
            writer.println(ways[n]);
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
