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

    int inv(int a) {
        return a == 1 ? 1 : (int)((long)(MOD - MOD / a) * inv(MOD % a) % MOD);
    }

    int add(int a, int b) {
        a += b;
        if (a >= MOD) {
            a -= MOD;
        }
        return a;
    }

    public void run() {
        InputReader reader = new InputReader(System.in);
        PrintWriter writer = new PrintWriter(System.out);
        try {
            int n = reader.nextInt();
            int[] a = new int[n];
            for (int i = 0; i < n; ++ i) {
                a[i] = reader.nextInt();
            }
            int[] sum = new int[n + 1];
            sum[0] = 1;
            for (int i = 0; i < n; ++ i) {
                for (int j = i + 1; j >= 1; -- j) {
                    sum[j] = add(sum[j], (int)((long)sum[j - 1] * a[i] % MOD));
                }
            }
            int[] ways = sum;
            for (int r = n; r >= 2; -- r) {
                int denum = inv(r * (r - 1));
                int[] newWays = new int[n + 1];
                for (int one = 1; one <= r; ++ one) {
                    int zero = r - one;
                    newWays[one] = add(newWays[one], (int)((long)ways[one] * (zero * (zero - 1) + zero * one) % MOD * denum % MOD));
                    newWays[one - 1] = add(newWays[one - 1], (int)((long)ways[one] * (one * (one - 1) / 2) % MOD * denum % MOD));
                }
                ways = newWays;
            }
            writer.println(ways[1]);
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
