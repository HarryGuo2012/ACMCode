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

    int     n;
    int[]   a;
    int[][] sum;

    int signum(int x) {
        if (x == 0) {
            return 0;
        }
        return x < 0 ? -1 : 1;
    }

    int getSum(int x0, int x1, int y0, int y1) {
        x0 ++;
        y0 ++;
        return sum[x0][y0] - sum[x0][y1] - sum[x1][y0] + sum[x1][y1];
    }

    long solve(int[] p) {
        int[] iterators;
        if (Math.abs(p[1] - p[3]) != 1) {
            iterators = new int[]{0, 2};
        } else if (Math.abs(p[0] - p[3]) != 1) {
            iterators = new int[]{1, 2};
        } else if (Math.abs(p[0] - p[2]) != 1) {
            iterators = new int[]{1, 3};
        } else {
            iterators = new int[]{1, 2};
        }
        int[] pIterators = new int[]{p[iterators[0]], p[iterators[1]]};
        int tmpSignum = signum(pIterators[0] - pIterators[1]);
        long result = 0;
        for (int i = 0; i < n; ++ i) {
            for (int j = i + 1; j < n; ++ j) {
                if (signum(a[i] - a[j]) == tmpSignum) {
                    int[] lowerBound = new int[]{-1, -1, -1, -1};
                    int[] upperBound = new int[]{n,  n,  n,  n};
                    lowerBound[pIterators[0]] = upperBound[pIterators[0]] = a[i];
                    lowerBound[pIterators[1]] = upperBound[pIterators[1]] = a[j];
                    for (int k = 1; k < 4; ++ k) {
                        lowerBound[k] = Math.max(lowerBound[k], lowerBound[k - 1]);
                    }
                    for (int k = 2; k >= 0; -- k) {
                        upperBound[k] = Math.min(upperBound[k], upperBound[k + 1]);
                    }
                    long product = 1;
                    if (iterators[0] != 0) {
                        int x = p[0];
                        product *= getSum(-1, i, lowerBound[x], upperBound[x]);
                    }
                    if (iterators[0] + 1 != iterators[1]) {
                        int x = p[iterators[0] + 1];
                        product *= getSum(i, j, lowerBound[x], upperBound[x]);
                    }
                    if (iterators[1] != 3) {
                        int x = p[3];
                        product *= getSum(j, n, lowerBound[x], upperBound[x]);
                    }
                    result += product;
                }
            }
        }
        return result;
    }

    public void run() {
        InputReader reader = new InputReader(System.in);
        PrintWriter writer = new PrintWriter(System.out);
        try {
            n = reader.nextInt();
            int[] p = new int[4];
            for (int i = 0; i < 4; ++ i) {
                p[i] = reader.nextInt() - 1;
            }
            a = new int[n];
            for (int i = 0; i < n; ++ i) {
                a[i] = reader.nextInt() - 1;
            }
            sum = new int[n + 1][n + 1];
            for (int i = 0; i < n; ++ i) {
                sum[i][a[i]] ++;
            }
            for (int i = n - 1; i >= 0; -- i) {
                for (int j = n - 1; j >= 0; -- j) {
                    sum[i][j] += sum[i + 1][j] + sum[i][j + 1] - sum[i + 1][j + 1];
                }
            }
            long result = solve(p);
            boolean flag = true;
            if (Arrays.equals(p, new int[]{1, 3, 0, 2})) {
                result -= solve(new int[]{2, 3, 0, 1});
            } else if (Arrays.equals(p, new int[]{2, 0, 3, 1})) {
                result -= solve(new int[]{1, 0, 3, 2});
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
