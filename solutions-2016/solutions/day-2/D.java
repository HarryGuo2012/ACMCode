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
        PrintWriter writer = new PrintWriter(System.out);
        try {
            while (true) {
                int n = reader.nextInt();
                int m = reader.nextInt();
                int[] a = new int[n];
                for (int i = 0; i < n; ++ i) {
                    a[i] = reader.nextInt() - 1;
                }
                int[][][] ways = new int[1][2][m + 1];
                ways[0][0][0] = ways[0][1][0] = 1;
                for (int j = 1; j < n; ++ j) {
                    int[][][] newWays = new int[j + 1][2][m + 1];
                    for (int value = 0; value < j; ++ value) {
                        for (int side = 0; side < 2; ++ side) {
                            int lvalue = side == 0 ? j - 1 : value;
                            int rvalue = side == 0 ? value : j - 1;
                            for (int i = 0; i <= m; ++ i) {
                                newWays[rvalue][0][i] = add(newWays[rvalue][0][i], ways[value][side][i]);
                                if (a[j] > a[lvalue] && i < m) {
                                    newWays[rvalue][0][i + 1] = add(newWays[rvalue][0][i + 1], ways[value][side][i]);
                                }
                                newWays[lvalue][1][i] = add(newWays[lvalue][1][i], ways[value][side][i]);
                                if (a[rvalue] > a[j] && i < m) {
                                    newWays[lvalue][1][i + 1] = add(newWays[lvalue][1][i + 1], ways[value][side][i]);
                                }
                            }
                        }
                    }
                    ways = newWays;
                }
                int[][] stirling = new int[m + 1][m + 1];
                stirling[0][0] = 1;
                for (int i = 1; i <= m; ++ i) {
                    for (int j = 1; j <= i; ++ j) {
                        stirling[i][j] = (int)((stirling[i - 1][j - 1] + (long)j * stirling[i - 1][j]) % MOD);
                    }
                }
                int[] factorial = new int[m + 1];
                factorial[0] = 1;
                for (int i = 1; i <= m; ++ i) {
                    factorial[i] = (int)((long)i * factorial[i - 1] % MOD);
                }
                int result = 0;
                for (int value = 0; value < n; ++ value) {
                    for (int side = 0; side < 2; ++ side) {
                        for (int i = 0; i <= m; ++ i) {
                            result = add(result, (int)((long)stirling[m][i] * factorial[i] % MOD * ways[value][side][i] % MOD));
                        }
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
