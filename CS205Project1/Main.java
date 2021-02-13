import java.io.*;
import java.security.SecureRandom;
import java.util.StringTokenizer;

public class Main {
    private static long xp,yp,zp;
    public static void main(String[] args) {
        initiateRandom();
        JavaMatrix jm1 = new JavaMatrix(5000, 5000);
        JavaMatrix jm2 = new JavaMatrix(5000, 5000);
        for (int i = 0; i < 5000; i++) {
            for (int j = 0; j < 5000; j++) {
                jm1.set(i,j,randomGenerate());
                jm2.set(i,j,randomGenerate());
            }
        }
        System.out.println("A:");
        jm1.printJM();
        System.out.println("B:");
        jm2.printJM();
        System.out.println("A*B:");
        long t1 = System.currentTimeMillis();
        (jm1.multiply(jm2)).printJM();
        long t2 = System.currentTimeMillis();
        System.out.println((t2 - t1) + "ms");
    }
    private static void initiateRandom(){
        SecureRandom sr=new SecureRandom();
        sr.setSeed(System.currentTimeMillis());
        xp=sr.nextLong();
        yp=sr.nextLong();
        zp=sr.nextLong();
    }
    private static float randomGenerate(){
        xp^=xp<<3;
        xp^=xp>>7;
        xp^=xp<<1;
        long t=xp;
        xp=yp;
        yp=zp;
        zp=t^xp^yp;
        return zp*1.0f/Integer.MAX_VALUE;
    }
    private static class Reader {
        BufferedReader in;
        StringTokenizer tokenizer;

        public Reader(InputStream inputStream) {
            in = new BufferedReader(new InputStreamReader(inputStream));
        }

        private String next() {
            while (tokenizer == null || !tokenizer.hasMoreTokens()) {
                try {
                    tokenizer = new StringTokenizer(in.readLine());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            return tokenizer.nextToken();
        }

        public int nextInt() {
            return Integer.parseInt(next());
        }
    }
}
