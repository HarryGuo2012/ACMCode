import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;

public class Solution {
    public static void main(String[] args) {
        new Solution().run();
    }

    class Part {
        Part(int start, int which) {
            this.start = start;
            this.which = which;
        }

        int start, which;
    }

    int n, s;
    int[] a, aa;
    long[] result;
    long[][] dp;
    Part[] queue;
    List<List<Integer>> children;

    long eval(int i, int j) {
        return dp[s][i] + dp[i + 1][j];
    }

    void dfs(int u) {
        a[-- s] = aa[u];
        dp[s][s] = a[s];
        int head = 0;
        int tail = 0;
        queue[tail ++] = new Part(s, s);
        long sum = a[s];
        for (int i = s + 1; i < n; ++ i) {
            sum += a[i];
            while (head + 1 < tail && queue[head + 1].start <= i) {
                head ++;
            }
            dp[s][i] = eval(queue[head].which, i) + sum;
            while (true) {
                int low = Math.max(i + 1, queue[tail - 1].start);
                int high = n;
                while (low < high) {
                    int middle = low + high >> 1;
                    if (eval(queue[tail - 1].which, middle) < eval(i, middle)) {
                        low = middle + 1;
                    } else {
                        high = middle;
                    }
                }
                if (high <= queue[tail - 1].start) {
                    tail --;
                } else {
                    queue[tail ++] = new Part(high, i);
                    break;
                }
            }
        }
        result[u] = dp[s][n - 1];
        for (int v : children.get(u)) {
            dfs(v);
        }
        s ++;
    }

    public void run() {
        InputReader reader = new InputReader(System.in);
        PrintWriter writer = new PrintWriter(System.out);
        try {
            n = reader.nextInt();
            aa = new int[n];
            children = new ArrayList<List<Integer>>();
            for (int i = 0; i < n; ++ i) {
                aa[i] = reader.nextInt();
                children.add(new ArrayList<Integer>());
            }
            for (int i = 1; i < n; ++ i) {
                children.get(reader.nextInt() - 1).add(i);
            }
            result = new long[n];
            a = new int[n];
            queue = new Part[n];
            dp = new long[n][n];
            s = n;
            dfs(0);
            for (int i = 0; i < n; ++ i) {
                writer.println(result[i]);
            }
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
