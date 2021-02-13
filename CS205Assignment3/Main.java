import java.io.*;
import java.security.SecureRandom;
public class Main {
    private static Reader in;
    private static PrintWriter out;
    private static final int thread_Number=Runtime.getRuntime().availableProcessors();
    private static float[]vector1;
    private static float[]vector2;
    private static double[] results;
    private static double result;
    private static int size;
    private static long xp,yp,zp;

    public static void main(String[] args) throws InterruptedException {
        improveJavaIO();
        javaInSize();
        initiate();
        long t0=System.currentTimeMillis();
        javaInElements(1);
        javaInElements(2);
        long t1=System.currentTimeMillis();
        out.println("Data IO Times:"+(t1-t0)+"ms");
        out.flush();

        singleThreadMethod();
        Main.result=0;
        multiplyThreadMethod();
    }
    private static void improveJavaIO(){
        in=new Reader();
        out= new PrintWriter(new OutputStreamWriter(System.out));
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
    private static void javaInSize(){
        try{
            size=Integer.parseInt(in.readLine());
        }catch (IOException ioe){
            ioe.printStackTrace();
        }
    }
    private static void initiate(){
        SecureRandom sr=new SecureRandom();
        xp=sr.nextLong();
        yp=sr.nextLong();
        zp=sr.nextLong();
        vector1=new float[size];
        vector2=new float[size];
        results=new double[thread_Number];
    }
    private static void javaInElements(int signNumber){
        if(signNumber==1){
            for (int i = 0; i < size; ++i) {
                vector1[i]=randomGenerate();
            }
        }else {
            for (int i = 0; i < size; ++i) {
                vector2[i]=randomGenerate();
            }
        }
    }
    private static void singleThreadMethod(){
        long t1=System.currentTimeMillis();
        for (int i=0;i<size;i++){
            Main.result+=vector1[i]*vector2[i];
        }
        out.printf("%.4f%n",Main.result);
        long t2=System.currentTimeMillis();
        out.println((t2-t1)+"ms");
        out.flush();
    }
    private static void multiplyThreadMethod()throws InterruptedException{
        long t3=System.currentTimeMillis();
        MyThread[]mts=new MyThread[thread_Number];
        Thread[]threadsPool=new Thread[thread_Number];
        int each=size/thread_Number;
        int start=0,end=each;

        for (int i=0;i<thread_Number;i++){
            if(i==thread_Number-1){
                end=size;
            }
            mts[i]=new MyThread(start,end,i);
            start=end;
            end+=each;
        }

        for (int i = 0; i < thread_Number; i++) {
            threadsPool[i]=new Thread(mts[i]);
            threadsPool[i].start();
        }
        for (Thread t:threadsPool){
            t.join();
        }
        double r=0;
        for(double d:results){
            r+=d;
        }
        System.out.printf("%.4f%n",r);
        long t4=System.currentTimeMillis();
        System.out.println((t4-t3)+"ms");
    }

    static class MyThread implements Runnable{
        private final int start;
        private final int end;
        private final int sign;
        public MyThread(int start,int end,int sign){
            this.start=start;
            this.end=end;
            this.sign=sign;
        }

        @Override
        public void run() {
            double re=0;
            for (int i=start;i<end;i++){
                re+=vector1[i]*vector2[i];
            }
            results[sign]=re;
        }
    }
    static class Reader {
        final private int BUFFER_SIZE = 1 << 16;
        private final DataInputStream din;
        private final byte[] buffer;
        private int bufferPointer, bytesRead;

        public Reader()
        {
            din = new DataInputStream(System.in);
            buffer = new byte[BUFFER_SIZE];
            bufferPointer = bytesRead = 0;
        }

        public String readLine() throws IOException
        {
            byte[] buf = new byte[64]; // line length
            int cnt = 0, c;
            while ((c = read()) != -1)
            {
                if (c == '\n')
                    break;
                buf[cnt++] = (byte) c;
            }
            return new String(buf, 0, cnt);
        }

        public int nextInt() throws IOException
        {
            int ret = 0;
            byte c = read();
            while (c <= ' ')
                c = read();
            boolean neg = (c == '-');
            if (neg)
                c = read();
            do
            {
                ret = ret * 10 + c - '0';
            }  while ((c = read()) >= '0' && c <= '9');

            if (neg)
                return -ret;
            return ret;
        }

        public long nextLong() throws IOException
        {
            long ret = 0;
            byte c = read();
            while (c <= ' ')
                c = read();
            boolean neg = (c == '-');
            if (neg)
                c = read();
            do {
                ret = ret * 10 + c - '0';
            }
            while ((c = read()) >= '0' && c <= '9');
            if (neg)
                return -ret;
            return ret;
        }

        public double nextDouble() throws IOException
        {
            double ret = 0, div = 1;
            byte c = read();
            while (c <= ' ')
                c = read();
            boolean neg = (c == '-');
            if (neg)
                c = read();

            do {
                ret = ret * 10 + c - '0';
            }
            while ((c = read()) >= '0' && c <= '9');

            if (c == '.')
            {
                while ((c = read()) >= '0' && c <= '9')
                {
                    ret += (c - '0') / (div *= 10);
                }
            }

            if (neg)
                return -ret;
            return ret;
        }

        private void fillBuffer() throws IOException
        {
            bytesRead = din.read(buffer, bufferPointer = 0, BUFFER_SIZE);
            if (bytesRead == -1)
                buffer[0] = -1;
        }

        private byte read() throws IOException
        {
            if (bufferPointer == bytesRead)
                fillBuffer();
            return buffer[bufferPointer++];
        }

        public void close() throws IOException
        {
            if (din == null)
                return;
            din.close();
        }
    }
}
