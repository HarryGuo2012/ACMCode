import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.ArrayList;
import java.util.List;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Set;
import java.util.TreeSet;
import java.util.StringTokenizer;

public class Solution {
    public static void main(String[] args) {
        new Solution().run();
    }

    static int INFINITY = 1000000000;

    class Edge {
        Edge(int to, int capacity, int cost) {
            this.to = to;
            this.capacity = capacity;
            this.cost = cost;
        }

        int to, capacity, cost;
        Edge back;
    }

    void addEdge(List<List<Edge>> edges, int a, int b, int ca, int co) {
        Edge u = new Edge(b, ca, co);
        Edge v = new Edge(a, 0, -co);
        u.back = v;
        v.back = u;
        edges.get(a).add(u);
        edges.get(b).add(v);
    }

    public void run() {
        InputReader reader = new InputReader(System.in);
        PrintWriter writer = new PrintWriter(System.out);
        try {
            int n = reader.nextInt();
            int m = reader.nextInt();
            int[][] edgeFace = new int[n][n];
            for (int i = 0; i < n; ++ i) {
                Arrays.fill(edgeFace[i], -1);
            }
            List<List<Integer>> faces = new ArrayList<List<Integer>>();
            faces.add(new ArrayList<Integer>());
            for (int i = 0; i < m; ++ i) {
                int k = reader.nextInt();
                List<Integer> face = new ArrayList<Integer>();
                for (int j = 0; j < k; ++ j) {
                    face.add(reader.nextInt() - 1);
                }
                for (int j = 0; j < k; ++ j) {
                    edgeFace[face.get(j)][face.get((j + 1) % k)] = i + 1;
                }
                faces.add(face);
            }
            if (true) {
                Set<Integer> unorderedOuterFace = new TreeSet<Integer>();
                for (int i = 0; i < n; ++ i) {
                    for (int j = 0; j < n; ++ j) {
                        if (edgeFace[j][i] != -1 && edgeFace[i][j] == -1) {
                            edgeFace[i][j] = 0;
                            unorderedOuterFace.add(i);
                        }
                    }
                }
                List<Integer> face = new ArrayList<Integer>();
                face.addAll(unorderedOuterFace);
                faces.set(0, face);
            }
            int[] degree = new int[n];
            for (List<Integer> face : faces) {
                for (int v : face) {
                    degree[v] ++;
                }
            }
            List<List<Edge>> graph = new ArrayList<List<Edge>>();
            int vv = n + faces.size() + 2;
            for (int i = 0; i < vv; ++ i) {
                graph.add(new ArrayList<Edge>());
            }
            int source = n + faces.size();
            int target = source + 1;
            for (int i = 0; i < n; ++ i) {
                addEdge(graph, source, i, 4 - degree[i], 0);
                for (int j = 0; j < n; ++ j) {
                    if (edgeFace[i][j] != -1) {
                        int u = n + edgeFace[i][j];
                        int v = n + edgeFace[j][i];
                        addEdge(graph, u, v, INFINITY, 1);
                    }
                }
            }
            for (int j = 0; j < faces.size(); ++ j) {
                List<Integer> face = faces.get(j);
                for (int i : face) {
                    addEdge(graph, i, n + j, 3, 0);
                }
                int demand = face.size();
                if (j > 0) {
                    demand -= 4;
                } else {
                    demand += 4;
                }
                if (demand > 0) {
                    addEdge(graph, n + j, target, demand, 0);
                } else {
                    addEdge(graph, source, n + j, -demand, 0);
                }
            }
            int result = 0;
            while (true) {
                int[] distance = new int[vv];
                Arrays.fill(distance, Integer.MAX_VALUE);
                distance[source] = 0;
                boolean[] visited = new boolean[vv];
                Edge[] back = new Edge[vv];
                Queue<Integer> queue = new LinkedList<Integer>();
                queue.offer(source);
                while (!queue.isEmpty()) {
                    int u = queue.poll();
                    visited[u] = false;
                    for (Edge e : graph.get(u)) {
                        int v = e.to;
                        if (e.capacity > 0 && distance[u] + e.cost < distance[v]) {
                            distance[v] = distance[u] + e.cost;
                            back[v] = e;
                            if (!visited[v]) {
                                visited[v] = true;
                                queue.offer(v);
                            }
                        }
                    }
                }
                if (distance[target] == Integer.MAX_VALUE) {
                    break;
                }
                for (int v = target; v != source; ) {
                    Edge e = back[v];
                    e.capacity --;
                    e.back.capacity ++;
                    v = e.back.to;
                    result += e.cost;
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
