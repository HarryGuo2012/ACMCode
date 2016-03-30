import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;
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
            int l = n + 63 >> 6;
            long[][] graph = new long[n][l];
            for (int i = 0; i < n; ++ i) {
                String buffer = reader.nextToken();
                for (int j = 0; j < n; ++ j) {
                    if (buffer.charAt(j) == '1') {
                        graph[i][j >> 6] |= 1L << (j & 63);
                    }
                }
            }
            long result = 0;
            for (int s = 0; s < n; ++ s) {
                int[] distance = new int[n];
                Arrays.fill(distance, n);
                distance[s] = 0;
                long[] global = new long[l];
                global[s >> 6] |= 1L << (s & 63);
                Queue<Integer> queue = new LinkedList<Integer>();
                queue.offer(s);
                while (!queue.isEmpty()) {
                    int u = queue.poll();
                    for (int i = 0; i < l; ++ i) {
                        long mask = graph[u][i] & (~global[i]);
                        while (mask != 0) {
                            int k = Long.numberOfTrailingZeros(mask);
                            int v = i << 6 | k;
                            distance[v] = distance[u] + 1;
                            queue.offer(v);
                            mask ^= 1L << k;
                            global[i] ^= 1L << k;
                        }
                    }
                }
                for (int t = 0; t < n; ++ t) {
                    result += distance[t] * distance[t];
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
