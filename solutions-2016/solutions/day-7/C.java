import java.io.*;
import java.util.Locale;
import java.util.StringTokenizer;

public class spotlights_ma_linear {
    private final InputReader reader;
    private final OutputWriter writer;

    public spotlights_ma_linear(InputReader reader, OutputWriter writer) {
        this.reader = reader;
        this.writer = writer;
    }

    public static void main(String[] args) {
        InputReader reader = new InputReader(System.in);
        OutputWriter writer = new OutputWriter(System.out);
        new spotlights_ma_linear(reader, writer).run();
        writer.writer.flush();
    }

    public void run() {
        int n = reader.nextInt();
        final int MAX = 1296 * 1000;
        int[] bal = new int[MAX + 1];
        for (int i = 0; i < n; i++) {
            int x = reader.nextInt(), y = reader.nextInt();
            int phi = reader.nextInt(), alpha = reader.nextInt();
            if (alpha + phi <= MAX) {
                bal[alpha]++;
                bal[alpha + phi]--;
            } else {
                bal[alpha]++;
                bal[MAX]--;
                bal[0]++;
                bal[alpha + phi - MAX]--;
            }
        }
        int cur = 0;
        for (int x = 0; x < MAX; x++) {
            cur += bal[x];
            if (cur == 0) {
                double ang = 2 * Math.PI / MAX * (x + 0.5);
                final double R = 8e8;
                double x0 = R * Math.cos(ang), y0 = R * Math.sin(ang);
                writer.printf("YES\n%d %d\n", (long)x0, (long)y0);
                return;
            }
        }
        throw new AssertionError();
    }


    static class InputReader {
        public BufferedReader reader;
        public StringTokenizer tokenizer;

        public InputReader(InputStream stream) {
            reader = new BufferedReader(new InputStreamReader(stream), 32768);
            tokenizer = null;
        }

        public String next() {
            while (tokenizer == null || !tokenizer.hasMoreTokens()) {
                try {
                    tokenizer = new StringTokenizer(reader.readLine());
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            }
            return tokenizer.nextToken();
        }

        public int nextInt() {
            return Integer.parseInt(next());
        }

        public double nextDouble() {
            return Double.parseDouble(next());
        }

        public long nextLong() {
            return Long.parseLong(next());
        }
    }

    static class OutputWriter {
        public PrintWriter writer;

        OutputWriter(OutputStream stream) {
            writer = new PrintWriter(stream);
        }

        public void printf(String format, Object... args) {
            writer.print(String.format(Locale.ENGLISH, format, args));
        }
    }
}

