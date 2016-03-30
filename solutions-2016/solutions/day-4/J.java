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

    static int MOD = 2016;

    class Entry {
        Entry() {
            value = 0;
            plan = new ArrayList<Integer>();
        }

        Entry(int k, int v) {
            value = v % MOD;
            plan = new ArrayList<Integer>();
            plan.add(k);
        }

        void merge(Entry other) {
            value += other.value;
            if (value >= MOD) {
                value -= MOD;
            }
            plan.addAll(other.plan);
        }

        @Override
        public String toString() {
            return plan.toString();
        }

        int value;
        List<Integer> plan;
    }

    List<Entry> bootstrap(List<Entry> entries, int mod) {
        List<Entry> newEntries = new ArrayList<Entry>();
        List<Entry> buffer = new ArrayList<Entry>();
        for (Entry entry : entries) {
            buffer.add(entry);
            if (buffer.size() >= 2 * mod - 1) {
                boolean found = false;
                for (int mask = 0; mask < 1 << 2 * mod - 1; ++ mask) {
                    if (Integer.bitCount(mask) == mod) {
                        int sum = 0;
                        for (int i = 0; i < 2 * mod - 1; ++ i) {
                            if ((mask & (1 << i)) > 0) {
                                sum += buffer.get(i).value;
                            }
                        }
                        if (sum % mod == 0) {
                            found = true;
                            Entry newEntry = new Entry();
                            List<Entry> newBuffer = new ArrayList<Entry>();
                            for (int i = 0; i < 2 * mod - 1; ++ i) {
                                Entry e = buffer.get(i);
                                if ((mask & (1 << i)) > 0) {
                                    newEntry.merge(e);
                                } else {
                                    newBuffer.add(e);
                                }
                            }
                            newEntry.value /= mod;
                            newEntries.add(newEntry);
                            buffer = newBuffer;
                            break;
                        }
                    }
                }
                assert found;
            }
        }
        return newEntries;
    }

    public void run() {
        InputReader reader = new InputReader(System.in);
        PrintWriter writer = new PrintWriter(System.out);
        try {
            int n = 6666;
            int[] a = new int[n];
            for (int i = 0; i < n; ++ i) {
                a[i] = reader.nextInt();
            }
            List<Entry> entries = new ArrayList<Entry>();
            for (int i = 0; i < MOD * 2 - 1; ++ i) {
                entries.add(new Entry(i, a[i]));
            }
            for (int mod : new int[]{2, 2, 2, 2, 2, 3, 3, 7}) {
                entries = bootstrap(entries, mod);
                assert !entries.isEmpty();
            }
            List<Integer> plan = entries.get(0).plan;
            for (int index : plan) {
                writer.println(index + 1);
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
