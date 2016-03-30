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
    static int INV_2 = (int)5e8 + 4;

    int add(int x, int a) {
        x += a;
        while (x >= MOD) {
            x -= MOD;
        }
        return x;
    }

    public void run() {
        InputReader reader = new InputReader(System.in);
        PrintWriter writer = new PrintWriter(System.out);
        try {
            int n = reader.nextInt();
            int m = reader.nextInt();
            int[] a = new int[n];
            int[] count = new int[m];
            for (int i = 0; i < n; ++ i) {
                a[i] = reader.nextInt() - 1;
                count[a[i]] ++;
            }
            int[] w = new int[n + 1];
            for (int i = 1; i <= n; ++ i) {
                w[i] = (int)((((2L * i + 3) * i % MOD + 3) * i % MOD + 3) % MOD);
            }
            if (true) {
                int s = 0, s2 = 0;
                for (int i = 1; i <= n; ++ i) {
                    w[i] = add(w[i], s2 + MOD - (int)((i + 1L) * s % MOD));
                    s = add(s, w[i]);
                    s2 = add(s2, (int)((long)w[i] * i % MOD));
                }
            }
            int[] power2 = new int[n + 1];
            power2[0] = 1;
            for (int i = 1; i <= n; ++ i) {
                power2[i] = (power2[i - 1] << 1) % MOD;
            }
            int[] s = w.clone();
            if (true) {
                int power2inv = 1;
                for (int i = 1; i <= n; ++ i) {
                    power2inv = (int)((long)power2inv * INV_2 % MOD);
                    s[i] = (int)((long)s[i] * power2inv % MOD);
                }
                for (int i = 1; i <= n; ++ i) {
                    s[i] = add(s[i], s[i - 1]);
                }
            }
            int result = 0;
            int[] first = new int[m + 1];
            Arrays.fill(first, n);
            boolean[] coveredColor = new boolean[m];
            for (int i = n - 1; i >= 0; -- i) {
                if (true) {
                    int p = 0;
                    while (first[p] != n && a[i] != a[first[p]]) {
                        p ++;
                    }
                    for (int j = p; j >= 1; -- j) {
                        first[j] = first[j - 1];
                    }
                    first[0] = i;
                }
                coveredColor[a[i]] = true;
                int coveredLength = 0;
                int uncoveredWays = 1;
                for (int j = 0; j < m; ++ j) {
                    if (coveredColor[j]) {
                        coveredLength += count[j];
                    } else {
                        uncoveredWays = (int)((long)uncoveredWays * (power2[count[j]] - 1) % MOD);
                    }
                }
                for (int j = m - 1; j >= 0; -- j) {
                    if (first[j] == n) {
                        continue;
                    }
                    int c = a[first[j]];
                    result = add(result, (int)((long)power2[coveredLength] * (s[first[j + 1] - i] + MOD - s[first[j] - i]) % MOD * uncoveredWays % MOD));
                    coveredLength -= count[c];
                    uncoveredWays = (int)((long)uncoveredWays * (power2[count[c]] - 1) % MOD);
                }
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
