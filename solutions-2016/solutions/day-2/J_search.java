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

    int n;
    int[] order, parent;
    int[][] xor;
    long all, done;

    int[][] search(int count, int index, int mask) {
        if (index == n) {
            done ++;
            if (done % 1000000 == 0) {
                System.err.println(String.format("%d/%d = %.2f%%", done, all, (double)done / all * 100));
            }
            int total = 0;
            for (int j = 0; j < n; ++ j) {
                xor[j][j] = order[j];
                for (int i = 0; i < j; ++ i) {
                    xor[i][j] = (i < parent[j] ? xor[i][parent[j]] : xor[parent[j]][i])  ^ order[j];
                    if (xor[i][j] == 0) {
                        total ++;
                    }
                }
            }
            if (total > n) {
                int[][] result = new int[n - 1][2];
                for (int i = 1; i < n; ++ i) {
                    result[i - 1] = new int[]{order[parent[i]], order[i]};
                }
                return result;
            }
        } else if (index < count) {
            int backup = count;
            for (int subset = mask; ; subset = subset - 1 & mask) {
                for (int i = 2; i <= n; ++ i) {
                    if ((subset >> i & 1) > 0) {
                        order[count] = i;
                        parent[count ++] = index;
                    }
                }
                int[][] result = search(count, index + 1, mask ^ subset);
                count = backup;
                if (result != null) {
                    return result;
                }
                if (subset == 0) {
                    break;
                }
            }
        }
        return null;
    }

    public void run() {
        InputReader reader = new InputReader(System.in);
        PrintWriter writer = new PrintWriter(System.out);
        try {
            n = reader.nextInt();
            int m = (n + 1) / 2;
            int total = 0;
            for (int lenght = 2; lenght <= m; lenght += 2) {
                total += m - lenght + 1;
            }
            if (total > n) {
                writer.println("Yes");
                for (int i = 1; i < n; ++ i) {
                    writer.println("" + i + " " + (i + 1));
                }
            } else {
                parent = new int[n];
                order = new int[n];
                order[0] = 1;
                xor = new int[n][n];
                all = 1;
                for (int i = 0; i < n - 2; ++ i) {
                    all *= n;
                }
                done = 0;
                int[][] result = search(1, 0, (1 << n + 1) - 4);
                if (result != null) {
                    writer.println("Yes");
                    for (int i = 0; i < n - 1; ++ i) {
                        writer.println("" + result[i][0] + " " + result[i][1]);
                    }
                } else {
                    writer.println("No");
                }
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
