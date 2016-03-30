import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.StringTokenizer;

public class Slow {
    public static void main(String[] args) {
        new Slow().run();
    }

    static int MOD = (int)1e9 + 7;

    class Data {
        Data(int m, int w) {
            this.m = m;
            this.w = w;
        }

        Data add(int delta, int www) {
            return new Data(this.m + delta, (int)((long)this.w * www % MOD));
        }

        void update(Data other) {
            if (other.m > this.m) {
                this.w = 0;
                this.m = other.m;
            }
            if (other.m == this.m) {
                this.w += other.w;
                if (this.w >= MOD) {
                    this.w -= MOD;
                }
            }
        }

        @Override
        public String toString() {
            return String.format("(%d,%d)", m, w);
        }

        int m, w;
    };

    int[][] binom;

    Data[] solve(int[] w, int threshold) {
        int n = w.length;
        if (n <= 1 || w[0] + w[1] >= threshold) {
            Data[] result = new Data[n + 1];
            for (int i = 0; i <= n; ++ i) {
                result[i] = new Data(i * (n - i), binom[n][i]);
            }
            return result;
        }
        int j = n;
        while (w[0] + w[j - 1] >= threshold) {
            j --;
        }
        Data[] result = solve(Arrays.copyOfRange(w, 1, j), threshold);
        int m = result.length;
        result = Arrays.copyOf(result, m + 1);
        result[m] = new Data(0, 0);
        for (int i = m; i >= 1; -- i) {
            result[i].update(result[i - 1]);
        }
        Data[] newResult = new Data[n + 1];
        for (int i = 0; i <= n; ++ i) {
            newResult[i] = new Data(0, 0);
        }
        int extra = n - j;
        for (int i = 0; i <= m; ++ i) {
            for (int k = 0; k <= extra; ++ k) {
                newResult[i + k].update(result[i].add(i * (extra - k) + (m - i) * k + k * (extra - k), binom[extra][k]));
            }
        }
        return newResult;
    }

    public void run() {
        InputReader reader = new InputReader(System.in);
        PrintWriter writer = new PrintWriter(System.out);
        try {
            int n = reader.nextInt();
            binom = new int[n + 1][n + 1];
            for (int i = 0; i <= n; ++ i) {
                binom[i][0] = 1;
                for (int j = 1; j <= i; ++ j) {
                    binom[i][j] = (binom[i - 1][j - 1] + binom[i - 1][j]) % MOD;
                }
            }
            int m = reader.nextInt();
            int[] w = new int[n];
            for (int i = 0; i < n; ++ i) {
                w[i] = reader.nextInt();
            }
            Arrays.sort(w);
            Data[] ways = solve(w, m);
            Data result = new Data(0, 0);
            for (Data d : ways) {
                result.update(d);
            }
            writer.println("" + result.m + " " + result.w);
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
