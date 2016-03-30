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
            int n = reader.nextInt();
            int m = reader.nextInt();
            int[] weight = new int[n];
            for (int i = 0; i < n; ++ i) {
                weight[i] = reader.nextInt();
            }
            Arrays.sort(weight);
            for (int i = 0; i < n; ++ i) {
                int j = n - 1 - i;
                if (i < j) {
                    weight[i] ^= weight[j];
                    weight[j] ^= weight[i];
                    weight[i] ^= weight[j];
                }
            }
            int[] sum = new int[n + 1];
            sum[n] = 0;
            for (int i = n - 1; i >= 0; -- i) {
                sum[i] = sum[i + 1] + weight[i];
            }
            int[] sigma = new int[m];
            for (int i = 0; i < m; ++ i) {
                sigma[i] = reader.nextInt();
            }
            int[][] minimum = new int[n + 1][n + 1];
            for (int i = 0; i <= n; ++ i) {
                Arrays.fill(minimum[i], Integer.MAX_VALUE);
            }
            minimum[0][1] = 0;
            for (int level = 0; level < m; ++ level) {
                int[][] newMinimum = new int[n + 1][n + 1];
                for (int i = 0; i <= n; ++ i) {
                    Arrays.fill(newMinimum[i], Integer.MAX_VALUE);
                }
                for (int done = 0; done <= n; ++ done) {
                    for (int leaves = 0; leaves <= n; ++ leaves) {
                        if (minimum[done][leaves] == Integer.MAX_VALUE) {
                            continue;
                        }
                        int value = minimum[done][leaves] + sum[done];
                        int newLeaves = Math.min(leaves * sigma[level], n);
                        newMinimum[done][newLeaves] = Math.min(newMinimum[done][newLeaves], value);
                    }
                }
                minimum = newMinimum;
                for (int i = 0; i < n; ++ i) {
                    for (int j = 1; j <= n; ++ j) {
                        minimum[i + 1][j - 1] = Math.min(minimum[i + 1][j - 1], minimum[i][j]);
                    }
                }
            }
            int result = Integer.MAX_VALUE;
            for (int j = 0; j <= n; ++ j) {
                result = Math.min(result, minimum[n][j]);
            }
            writer.println(result);
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
