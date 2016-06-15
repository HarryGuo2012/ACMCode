import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws Exception {
        Scanner cin = new Scanner(System.in);
        int N = cin.nextInt(), M = cin.nextInt();
        int[][] dp = new int[2][M + 1];
        int[] a = new int[N + 1], b = new int[M + 1];
        for (int i = 1; i <= N; i++)
            a[i] = cin.nextInt();
        for (int j = 1; j <= M; j++)
            b[j] = cin.nextInt();
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= M; j++) {
                int u = i & 1;
                int v = 1 - u;
                dp[u][j] = Math.max(dp[u][j - 1], dp[v][j]);
                if (a[i] == b[j]) dp[u][j] = Math.max(dp[v][j - 1] + 1, dp[u][j]);
            }
        System.out.println(dp[N & 1][M] + 1);
    }
}