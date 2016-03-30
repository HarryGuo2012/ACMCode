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

    int add(int x, int a) {
        x += a;
        if (x >= MOD) {
            x -= MOD;
        }
        return x;
    }

    public void run() {
        InputReader reader = new InputReader(System.in);
        try {
            int n = reader.nextInt();
            int d = reader.nextInt();
            int[] a = new int[n];
            for (int i = 0; i < n; ++ i) {
                String buffer = reader.nextToken();
                for (int j = 0; j < d; ++ j) {
                    a[i] |= buffer.charAt(j) - '0' << j;
                }
            }
            int b = 1024;
            int result = 0;
            int[] dp = new int[n];
            int[] table = new int[1 << d];
            for (int i = 0; i < n; ++ i) {
                if (i % b == 0) {
                    Arrays.fill(table, 0);
                    for (int j = 0; j < i; ++ j) {
                        table[a[j]] = add(table[a[j]], dp[j]);
                    }
                    for (int j = 0; j < d; ++ j) {
                        for (int mask = (1 << d) - 1; mask >= 0; -- mask) {
                            if ((mask >> j & 1) == 1) {
                                table[mask] = add(table[mask], table[mask ^ 1 << j]);
                            }
                        }
                    }
                }
                dp[i] = add(1, table[a[i]]);
                for (int j = (i / b) * b; j < i; ++ j) {
                    if ((a[i] & a[j]) == a[j]) {
                        dp[i] = add(dp[i], dp[j]);
                    }
                }
                result = add(result, dp[i]);
            }
            PrintWriter writer = new PrintWriter(System.out);
            writer.println(result);
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
