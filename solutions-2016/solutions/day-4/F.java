import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.StringTokenizer;

public class Solution {
    static final int MOD = (int)1e9 + 7;

    public static void main(String[] args) {
        new Solution().run();
    }

    public void run() {
        InputReader reader = new InputReader(System.in);
        PrintWriter writer = new PrintWriter(System.out);
        try {
            int n = reader.nextInt();
            int m = reader.nextInt();
            int[] a = new int[n];
            for (int i = 0; i < n; ++ i) {
                a[i] = reader.nextInt() - 1;
            }
            int[] b = new int[m];
            for (int i = 0; i < m; ++ i) {
                b[i] = reader.nextInt() - 1;
            }
            boolean[] isLow  = new boolean[n];
            boolean[] isHigh = new boolean[n];
            for (int i = 0; i < n - 1; ++ i) {
                if (a[i] < a[i + 1]) {
                    isLow[i] = true;
                } else {
                    isHigh[i] = true;
                }
            }
            isLow[n - 1] = isHigh[n - 1] = true;
            int[][] ways = new int[n + 1][m + 1];
            for (int i = 0; i <= n; ++ i) {
                Arrays.fill(ways[i], -2);
            }
            ways[0][0] = m - 1;
            for (int i = 0; i < m; ++ i) {
                for (int l = n - 1; l >= 0; -- l) {
                    for (int low = 0; low <= b[i]; ++ low) {
                        if (b[i] <= ways[l][low]) {
                            if (isLow[l]) {
                                ways[l + 1][b[i] + 1] = Math.max(ways[l + 1][b[i] + 1], ways[l][low]);
                            }
                            if (isHigh[l]) {
                                ways[l + 1][low] = Math.max(ways[l + 1][low], b[i] - 1);
                            }
                        }
                    }
                }
            }
            boolean found = false;
            for (int low = 0; low <= m; ++ low) {
                found |= ways[n][low] != -2;
            }
            writer.println(found ? "Yes" : "No");
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
