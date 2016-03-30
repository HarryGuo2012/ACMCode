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

    int multiply(int a, int b) {
        return (int)((long)a * b % MOD);
    }

    int n, m;
    int[] x, y, id, ways;

    int solveX(int[] x, int mask) {
        int min = Integer.MIN_VALUE;
        int max = Integer.MAX_VALUE;
        for (int i = 0; i < n; ++ i) {
            if ((mask >> id[i] & 1) > 0) {
                min = Math.max(min, x[i] - m);
                max = Math.min(max, x[i] + m);
            }
        }
        int result = 0;
        for (int t = min; t <= max; ++ t) {
            int resultOne = 1;
            for (int i = 0; i < n; ++ i) {
                if ((mask >> id[i] & 1) > 0) {
                    resultOne = multiply(resultOne, ways[Math.abs(x[i] - t)]);
                }
            }
            result = add(result, resultOne);
        }
        return result;
    }

    int solve(int mask) {
        return multiply(solveX(x, mask), solveX(y, mask));
    }

    public void run() {
        InputReader reader = new InputReader(System.in);
        PrintWriter writer = new PrintWriter(System.out);
        try {
            while (true) {
                n = reader.nextInt();
                int a = reader.nextInt();
                int b = reader.nextInt();
                m = reader.nextInt();
                id = new int[n];
                for (int i = 0; i < n; ++ i) {
                    if (a <= i && i < a + b) {
                        id[i] = 1;
                    } else if (i >= a + b) {
                        id[i] = 2;
                    }
                }
                x = new int[n];
                y = new int[n];
                for (int i = 0; i < n; ++ i) {
                    int p = reader.nextInt();
                    int q = reader.nextInt();
                    x[i] = p - q;
                    y[i] = p + q;
                }
                ways = new int[1];
                ways[0] = 1;
                for (int k = 1; k <= m; ++ k) {
                    int[] newWays = new int[k + 1];
                    newWays[1] = ways[0];
                    for (int i = 1; i < k; ++ i) {
                        newWays[i - 1] = add(newWays[i - 1], ways[i]);
                        newWays[i + 1] = add(newWays[i + 1], ways[i]);
                    }
                    if (k > 1) {
                        newWays[0] = add(newWays[0], ways[1]);
                    }
                    ways = newWays;
                }
                long result = 0;
                result += multiply(solve(1), multiply(solve(2), solve(4)));
                result -= multiply(solve(1), solve(6));
                result -= multiply(solve(2), solve(5));
                result -= multiply(solve(4), solve(3));
                result += solve(7) * 2;
                writer.println((result % MOD + MOD) % MOD);
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
