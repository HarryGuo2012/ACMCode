import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;

public class Main {
    public static void main(String[] args) {
        new Main().run();
    }

    void dfs(int n, boolean[][] graph, List<List<Integer>> children, boolean[] visited, int u) {
        visited[u] = true;
        for (int v = 0; v < n; ++ v) {
            if (!visited[v] && graph[u][v]) {
                children.get(u).add(v);
                dfs(n, graph, children, visited, v);
            }
        }
    }

    List<Integer> solve(int n, List<List<Integer>> children, List<Integer> plan, int u) {
        plan.add(u);
        for (int v : children.get(u)) {
            for (int w : children.get(v)) {
                solve(n, children, plan, w);
            }
            plan.add(v);
        }
        return plan;
    }

    public void run() {
        InputReader reader = new InputReader(System.in);
        PrintWriter writer = new PrintWriter(System.out);
        try {
            int n = reader.nextInt();
            reader.nextInt();
            boolean[][] graph = new boolean[n][n];
            for (int i = 0; i < n; ++ i) {
                String buffer = reader.nextToken();
                for (int j = 0; j < n; ++ j) {
                    graph[i][j] = buffer.charAt(j) == '1';
                }
            }
            List<List<Integer>> children = new ArrayList<List<Integer>>();
            for (int i = 0; i < n; ++ i) {
                children.add(new ArrayList<Integer>());
            }
            dfs(n, graph, children, new boolean[n], 0);
            List<Integer> plan = solve(n, children, new ArrayList<Integer>(), 0);
            assert plan.size() == n;
            for (int i = 0; i < n; ++ i) {
                writer.print(plan.get(i) + 1);
                if (i + 1 < n) {
                    writer.print(" ");
                } else {
                    writer.println();
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
