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

    public void run() {
        InputReader reader = new InputReader(System.in);
        PrintWriter writer = new PrintWriter(System.out);
        try {
            while (true) {
                int n = reader.nextInt();
                int m = reader.nextInt();
                long[] sum = new long[n + 1];
                for (int i = 0; i < n; ++ i) {
                    sum[i + 1] = sum[i] + reader.nextInt();
                }
                long[] b = new long[n + 1];
                int s = 1;
                while (s <= n && 0 <= sum[s] && sum[s] <= m) {
                    s ++;
                }
                long d = 0;
                for (int i = s; i <= n;) {
                    long min = sum[i];
                    long max = sum[i];
                    int j = i + 1;
                    while (j <= n && Math.max(max, sum[j]) - Math.min(min, sum[j]) <= m) {
                        max = Math.max(max, sum[j]);
                        min = Math.min(min, sum[j]);
                        j ++;
                    }
                    b[i] = -d - min;
                    d += b[i];
                    i = j;
                }
                for (int i = 1; i <= n; ++ i) {
                    writer.print("" + b[i] + (i < n ? ' ' : '\n'));
                }
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
