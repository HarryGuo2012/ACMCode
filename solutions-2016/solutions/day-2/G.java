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

    static long floorDiv(long a, long b) {
        assert b > 0;
        if (a >= 0) {
            return a / b;
        }
        return (a - b + 1) / b;
    }

    static int signum(long x) {
        return x < 0 ? -1 : x > 0 ? 1 : 0;
    }

    class Eisenstein implements Comparable<Eisenstein> {
        Eisenstein(long x, long y) {
            this.x = x;
            this.y = y;
        }

        @Override
        public int compareTo(Eisenstein other) {
            if (norm2() != other.norm2()) {
                return signum(norm2() - other.norm2());
            }
            if (x != other.x) {
                return signum(x - other.x);
            }
            return signum(y - other.y);
        }

        @Override
        public String toString() {
            return "(" + x + "," + y + ")";
        }

        Eisenstein add(Eisenstein other) {
            return new Eisenstein(x + other.x, y + other.y);
        }

        Eisenstein subtract(Eisenstein other) {
            return new Eisenstein(x - other.x, y - other.y);
        }

        Eisenstein multiply(long scale) {
            return multiply(new Eisenstein(scale, 0));
        }

        Eisenstein multiply(Eisenstein other) {
            return new Eisenstein(x * other.x - y * other.y, x * other.y + y * other.x - y * other.y);
        }

        long det(Eisenstein other) {
            return x * other.y - y * other.x;
        }

        Eisenstein mod(Eisenstein other) {
            Eisenstein a = this;
            Eisenstein b = other;
            Eisenstein bPrime = b.multiply(new Eisenstein(0, 1));
            long d = b.det(bPrime);
            long p0 = floorDiv(a.det(bPrime), d);
            long q0 = floorDiv(b.det(a), d);
            Eisenstein r0 = a.subtract(b.multiply(p0)).subtract(bPrime.multiply(q0));
            for (long p = p0; p <= p0 + 1; ++ p) {
                for (long q = q0; q <= q0 + 1; ++ q) {
                    Eisenstein r = a.subtract(b.multiply(p)).subtract(bPrime.multiply(q));
                    if (r.norm() < r0.norm()) {
                        r0 = r;
                    }
                }
            }
            return r0;
       }

        long norm2() {
            return x * x + y * y;
        }

        long norm() {
            return norm2() - x * y;
        }

        long x, y;
    }

    public void run() {
        InputReader reader = new InputReader(System.in);
        PrintWriter writer = new PrintWriter(System.out);
        try {
            int t = reader.nextInt();
            while (t > 0) {
                t --;
                int x_1 = reader.nextInt();
                int y_1 = reader.nextInt();
                int x_2 = reader.nextInt();
                int y_2 = reader.nextInt();
                Eisenstein a = new Eisenstein(x_1, y_1);
                Eisenstein b = new Eisenstein(x_2, y_2);
                while (b.norm2() != 0) {
                    Eisenstein c = a;
                    a = b;
                    b = c.mod(a);
                }
                Eisenstein[] units = new Eisenstein[]{
                    new Eisenstein(-1, -1),
                    new Eisenstein(-1, 0),
                    new Eisenstein(0, -1),
                    new Eisenstein(0, 1),
                    new Eisenstein(1, 0),
                    new Eisenstein(1, 1)
                };
                Eisenstein result = a;
                for (Eisenstein unit : units) {
                    Eisenstein aPrime = a.multiply(unit);
                    if (aPrime.compareTo(result) > 0) {
                        result = aPrime;
                    }
                }
                writer.println("" + result.x + " " + result.y);
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
