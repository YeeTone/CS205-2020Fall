import java.util.Arrays;

public class JavaMatrix{
    private static final int thread_number=Runtime.getRuntime().availableProcessors();

    private boolean isSquare=false;
    private boolean isDiagonal=false;
    private boolean isIdentical=false;
    private boolean isZeroMatrix=false;
    private int nonZeroNumberNotMain=0;
    private int nonZeroNumberMain=0;
    private int nonOneNumberMain=0;
    private int nonZeroNumber=0;

    private int row=0;
    private int column=0;
    private float[] data= null;

    public static boolean isExpressedOmitted=true;

    public JavaMatrix(int r,int c){
        this.row=r;
        this.column=c;
        this.data=new float[row*column];
        System.gc();
        Arrays.fill(this.data,0);
        this.isZeroMatrix=true;
        this.isSquare=(r==c);
        if(isSquare){
            this.nonOneNumberMain=r;
            this.nonZeroNumber=0;
            this.nonZeroNumberNotMain=0;
            this.nonZeroNumberMain=0;
        }
    }
    public float get(int r,int c){
        if(r>=this.row||c>=this.column){
            System.err.println("Matrix Index out of Bound!");
            return 0.0f;
        }else if(r<0||c<0){
            System.err.println("Negative Index!");
            return 0.0f;
        }else {
            return this.data[r*this.column+c];
        }
    }
    public void set(int r,int c,float value){
        if(r>=this.row||c>=this.column){
            System.err.println("Matrix Index out of Bound2!");
            return;
        }else if(r<0||c<0){
            System.err.println("Negative Index!");
            return;
        }
        if(isSquare){
            if(r==c){
                if(value==1){
                    nonOneNumberMain-=1;
                }else if(data[r*column+c]==1){
                    nonOneNumberMain+=1;
                }
                if(value!=0){
                    nonZeroNumberMain+=1;
                }else{
                    nonZeroNumberMain-=1;
                }
            }else{
                if(value!=0){
                    nonZeroNumberNotMain+=1;
                }else{
                    nonZeroNumberNotMain-=1;
                }
            }
        }
        if(value!=0){
            nonZeroNumber+=1;
        }else{
            nonZeroNumber-=1;
        }
        this.data[r*column+c]=value;

        isZeroMatrix=(nonZeroNumber==0);
        isDiagonal=(isSquare&&nonZeroNumberNotMain==0);
        isIdentical=(isSquare&&isDiagonal&&nonOneNumberMain==0);
    }
    public void printJM(){
        if(JavaMatrix.isExpressedOmitted&&row>6&&column>6){
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    System.out.print(get(i,j)+" ");
                }
                System.out.print("... ");
                for (int j = 0; j < 3; ++j) {
                    System.out.print(get(i,column-3+j)+" ");
                }
                System.out.println();
            }
            System.out.println("...");
            for (int i = row-3; i < row; ++i) {
                for (int j = 0; j < 3; ++j) {
                    System.out.print(get(i,j)+" ");
                }
                System.out.print("... ");
                for (int j = 0; j < 3; ++j) {
                    System.out.print(get(i,column-3+j)+" ");
                }
                System.out.println();
            }
        }else if(JavaMatrix.isExpressedOmitted&&row>6){
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < column; ++j) {
                    System.out.print(get(i,j)+" ");
                }
                System.out.println();
            }
            System.out.println("... ");
            for (int i = row-3; i < row; ++i) {
                for (int j = 0; j < column; ++j) {
                    System.out.print(get(i,j)+" ");
                }
                System.out.println();
            }
        }else if(JavaMatrix.isExpressedOmitted&&column>6){
            for (int i = 0; i < row; ++i) {
                for (int j = 0; j < 3; ++j) {
                    System.out.print(get(i,j)+" ");
                }
                System.out.print("... ");
                for (int j = 0; j < 3; ++j) {
                    System.out.print(get(i,column-3+j)+" ");
                }
                System.out.println();
            }
        }else{
            for (int i = 0; i < this.row; ++i) {
                for (int j = 0; j < this.column; ++j) {
                    System.out.print(get(i,j)+" ");
                }
                System.out.println();
            }
        }
    }
    public void fill(float value){
        Arrays.fill(this.data,value);
        if(isSquare){
            if(value==0){
                nonZeroNumber=0;
                nonZeroNumberNotMain=0;
                nonZeroNumberMain=0;
            }else{
                nonZeroNumber=row*column;
                nonZeroNumberMain=row;
                nonZeroNumberNotMain=row*(column-1);
            }
            if(value==1){
                nonOneNumberMain=0;
            }
        }
        if(value!=0&&!isSquare){
            nonZeroNumber=row*column;
        }
        isZeroMatrix=(nonZeroNumber==0);
        isDiagonal=(isSquare&&nonZeroNumberNotMain==0);
        isIdentical=(isSquare&&isDiagonal&&nonOneNumberMain==0);
    }
    public void inverseSign(){
        for (int i = 0; i < row*column; i++) {
            if(data[i]==0){
                continue;
            }
            data[i]*=-1;
        }
    }
    public void setDiagonal(float value){
        if(!isSquare){
            System.err.println("The matrix is not a square!");
            return;
        }
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < row; ++j) {
                if(i!=j){
                    set(i,j,0);
                }else{
                    set(i,j,value);
                }
            }
        }
        this.nonZeroNumberMain=(value==0?0:1)*row;
        this.nonZeroNumber=(value==0?0:1)*row;
        this.nonZeroNumberNotMain=0;
        this.nonOneNumberMain=(value==1?0:1)*row;
        this.isDiagonal= true;
        this.isZeroMatrix=(value==0);
        this.isIdentical=(value==1);
    }
    public JavaMatrix transport(){
        JavaMatrix transported=new JavaMatrix(this.column,this.row);
        for (int i = 0; i < this.column; ++i) {
            for (int j = 0; j < this.row; ++j) {
                transported.set(i,j,this.get(j,i));
            }
        }
        return transported;
    }
    public static JavaMatrix getIdentity(int x){
        JavaMatrix identical=new JavaMatrix(x,x);
        for (int i = 0; i < x; ++i) {
            identical.set(i,i,1);
        }
        identical.nonOneNumberMain=0;
        identical.nonZeroNumberNotMain=0;
        identical.nonZeroNumberMain=x;
        identical.nonZeroNumber=x;
        identical.isIdentical=true;
        identical.isDiagonal=true;
        identical.isSquare=true;
        identical.isZeroMatrix=false;
        return identical;
    }
    public static JavaMatrix getZeros(int r,int c){
        //Very Simple
        return new JavaMatrix(r,c);
    }
    public JavaMatrix add(final JavaMatrix jm){
        try{
            return addMatrix(jm);
        }catch (InterruptedException ie){
            return new JavaMatrix(0,0);
        }
    }
    public JavaMatrix minus(final JavaMatrix jm){
        jm.inverseSign();
        JavaMatrix out = this.add(jm);
        jm.inverseSign();
        return out;
    }
    public JavaMatrix multiply(final JavaMatrix jm){
        try{
            if(!check2MatrixMultiplyMatch(this,jm)){
                System.err.println("These 2 Matrix Size is not Matched! No multiplication is allowed!");
                return new JavaMatrix(0,0);
            }
            if(this.isZeroMatrix||jm.isZeroMatrix){
                return zeroMatrixMultiplication(this,jm);
            }else if(this.isIdentical||jm.isIdentical){
                return identicalMatrixMultiplication(this,jm);
            }else if(this.isDiagonal||jm.isDiagonal){
                return diagonalMatrixMultiplication(this,jm);
            }else if(this.row==1){
                return vectorMultiply(this,jm);
            }else if(this.row<=thread_number){
                return singleMultiply(jm);
            }else{
                return multipleMultiply(jm);
            }
        }catch (InterruptedException ie){
            System.err.println("InterruptedException Thrown");
            return new JavaMatrix(0,0);
        }

    }
    public JavaMatrix quickPower(int x) {
        if (!isSquare) {
            System.err.println("This is not a square! No power can be calculated!");
            return new JavaMatrix(0, 0);
        }
        if (x < 0) {
            System.err.println("The pow number must be a natural number!");
            return new JavaMatrix(0, 0);
        }
        JavaMatrix res = getIdentity(this.row);
        JavaMatrix s = this.cloneMatrix();
        while (x != 0) {
            if ((x & 1) == 1) {
                res = res.multiply(s);
            }
            s = s.multiply(s);
            x >>= 1;
        }
        return res;
    }

    private static void subMultiply(final JavaMatrix jm1,final JavaMatrix jm2,int start,int end,float[] results){
        int i, k, j;
        int x = jm2.column / 8* 8;
        if(x==jm2.column){
            x-=8;
        }

        float jm_i_k;
        for (i = start; i < end; ++i) {
            for (k = 0; k < jm1.column; ++k) {
                jm_i_k = jm1.get(i, k);
                if (jm_i_k == 0) {
                    continue;
                }

                for (j = 0; j + 8 < jm2.column; j+=8) {
                    results[i * jm2.column + j] += jm_i_k * jm2.get(k, j);
                    results[i * jm2.column + j + 1] += jm_i_k * jm2.get(k, j + 1);
                    results[i * jm2.column + j + 2] += jm_i_k * jm2.get(k, j + 2);
                    results[i * jm2.column + j + 3] += jm_i_k * jm2.get(k, j + 3);
                    results[i * jm2.column + j + 4] += jm_i_k * jm2.get(k, j + 4);
                    results[i * jm2.column + j + 5] += jm_i_k * jm2.get(k, j + 5);
                    results[i * jm2.column + j + 6] += jm_i_k * jm2.get(k, j + 6);
                    results[i * jm2.column + j + 7] += jm_i_k * jm2.get(k, j + 7);
                }
                for (j = x; j < jm2.column; j++) {
                    results[i * jm2.column + j] += jm1.get(i, k) * jm2.get(k, j);
                }
            }
        }
    }
    private static void subAdd(final JavaMatrix jm1,final JavaMatrix jm2,int start,int end){
        for (int i = start; i < end; ++i) {
            jm1.data[i]=jm1.data[i]+jm2.data[i];
        }
    }
    private static void subVectorMultiply(final JavaMatrix jm1,final JavaMatrix jm2,int start,int end,float[] results,int i){
        double re=0;
        for (int j = start; j < end; ++j) {
            if(jm1.data[j]==0||jm2.data[j]==0){
                continue;
            }
            re+=jm1.data[j]*jm2.data[j];
        }
        results[i]=(float)re;
    }
    private static JavaMatrix vectorMultiply(final JavaMatrix vector1,final JavaMatrix vector2) throws InterruptedException {
        int vectorSize=vector1.column;
        int each=vectorSize/thread_number;
        int start=0,end=each;
        VectorRunnable[]runnablePool=new VectorRunnable[thread_number];
        Thread[]threadPool=new Thread[thread_number];
        float[] vectorResult=new float[thread_number];
        VectorRunnable.vector1=vector1;
        VectorRunnable.vector2=vector2;
        VectorRunnable.results=vectorResult;

        for (int i = 0; i < thread_number; i++) {
            if(i==thread_number-1){
                end=vectorSize;
            }
            runnablePool[i]=new VectorRunnable(start,end,i);
            start=end;
            end+=each;
        }
        for (int i = 0; i < thread_number; i++) {
            threadPool[i] = new Thread(runnablePool[i]);
            threadPool[i].start();
        }
        for (int i = 0; i < thread_number; i++) {
            threadPool[i].join();
        }
        double r=0;
        for (int i = 0; i < thread_number; ++i) {
            r+=vectorResult[i];
        }
        JavaMatrix out=new JavaMatrix(1,1);
        out.set(0,0,(float)r);
        return out;
    }
    private static class VectorRunnable implements Runnable{
        private static JavaMatrix vector1=null;
        private static JavaMatrix vector2=null;
        private static float[] results = null;
        private final int start;
        private final int end;
        private final int sign;
        public VectorRunnable(int s,int e,int i){
            this.start=s;
            this.end=e;
            this.sign=i;
        }
        @Override
        public void run() {
            JavaMatrix.subVectorMultiply(vector1,vector2,start,end,results,sign);
        }
    }
    private static boolean check2MatrixMultiplyMatch(final JavaMatrix jm1,final JavaMatrix jm2){
        return (jm1.column==jm2.row);
    }
    private static JavaMatrix zeroMatrixMultiplication(final JavaMatrix jm1,final JavaMatrix jm2){
        return new JavaMatrix(jm1.row,jm2.column);
    }
    private static JavaMatrix diagonalMatrixMultiplication(final JavaMatrix jm1,final JavaMatrix jm2){
        if(jm1.isDiagonal&&jm2.isDiagonal){
            JavaMatrix out=new JavaMatrix(jm1.row,jm1.row);
            for (int i = 0; i < jm1.row; ++i) {
                if(jm1.get(i,i)==0||jm2.get(i,i)==0){
                    continue;
                }
                out.set(i,i,jm1.get(i,i)*jm2.get(i,i));
            }
            return out;
        }else if(jm1.isDiagonal){
            JavaMatrix out=new JavaMatrix(jm1.row,jm2.column);
            for (int i = 0; i < jm1.row; ++i) {
                if(jm1.get(i,i)==0){
                    continue;
                }
                for (int j = 0; j < jm2.column; ++j) {
                    out.set(i,j,jm1.get(i,i)*jm2.get(i,j));
                }
            }
            return out;
        }else if(jm2.isDiagonal){
            JavaMatrix out=new JavaMatrix(jm1.row,jm2.column);
            for (int i = 0; i < jm2.column; ++i) {
                if(jm2.get(i,i)==0){
                    continue;
                }
                for (int j = 0; j < jm1.row; ++j) {
                    out.set(j,i,jm1.get(j,i)*jm2.get(i,i));
                }
            }
            return out;
        } else{
            return new JavaMatrix(0,0);
        }
    }
    private static JavaMatrix identicalMatrixMultiplication(final JavaMatrix jm1,final JavaMatrix jm2){
        if(jm1.isIdentical){
            return jm2;
        }else if(jm2.isIdentical){
            return jm1;
        }else {
            return new JavaMatrix(0,0);
        }
    }
    private JavaMatrix singleMultiply(final JavaMatrix jm){
        JavaMatrix output=new JavaMatrix(this.row,jm.column);
        for (int i = 0; i < this.row; ++i) {
            for (int j = 0; j < jm.column; ++j) {
                double value=0;
                for (int k = 0; k < this.column; ++k) {
                    if(get(i,k)!=0&&jm.get(k,j)!=0){
                        value+=get(i,k)*jm.get(k,j);
                    }
                }
                output.set(i,j,(float)value+output.get(i,j));
            }
        }
        return output;
    }
    private JavaMatrix multipleMultiply(final JavaMatrix jm) throws InterruptedException {
        MatrixRunnable[]runnablePool=new MatrixRunnable[thread_number];
        Thread[]threadsPool=new Thread[thread_number];
        int each=this.row/thread_number;
        int start=0,end=each;
        MatrixRunnable.jm1=this;
        MatrixRunnable.jm2=jm;
        MatrixRunnable.results=new float[(this.row)*(jm.column)];
        System.gc();
        for (int i = 0; i < thread_number; ++i) {
            if(i==thread_number-1){
                end=this.row;
            }
            runnablePool[i]=new MatrixRunnable(start,end);
            start=end;
            end+=each;
        }
        for (int i=0;i<thread_number; ++i){
            threadsPool[i]=new Thread(runnablePool[i]);
            threadsPool[i].start();
        }
        for (int i=0;i<thread_number; ++i){
            threadsPool[i].join();
        }
        JavaMatrix output=new JavaMatrix(this.row,jm.column);
        output.data=Arrays.copyOf(MatrixRunnable.results,MatrixRunnable.results.length);
        return output;
    }
    private static class MatrixRunnable implements Runnable{
        private static JavaMatrix jm1=null;
        private static JavaMatrix jm2=null;
        private static float[] results=null;
        private final int start;
        private final int end;
        public MatrixRunnable(int s,int e){
            this.start=s;
            this.end=e;
        }
        @Override
        public void run() {
            subMultiply(jm1,jm2,start,end,results);
        }
    }
    private JavaMatrix addMatrix(final JavaMatrix jm) throws InterruptedException {
        AdderRunnable[]runnablePool=new AdderRunnable[thread_number];
        Thread[]threadsPool=new Thread[thread_number];
        int total=this.row*this.column;
        int each=total/thread_number;
        int start=0,end=each;
        AdderRunnable.jm1=this;
        AdderRunnable.jm2=jm;
        System.gc();
        for (int i = 0; i < thread_number; ++i) {
            if(i==thread_number-1){
                end=total;
            }
            runnablePool[i]=new AdderRunnable(start,end);
            start=end;
            end+=each;
        }
        for (int i=0;i<thread_number; ++i){
            threadsPool[i]=new Thread(runnablePool[i]);
            threadsPool[i].start();
        }
        for (int i=0;i<thread_number; ++i){
            threadsPool[i].join();
        }
        return this;
    }
    private static class AdderRunnable implements Runnable{
        private static JavaMatrix jm1=null;
        private static JavaMatrix jm2=null;
        private final int start;
        private final int end;
        public AdderRunnable(int s,int e){
            this.start=s;
            this.end=e;
        }
        @Override
        public void run() {
            subAdd(jm1,jm2,start,end);
        }
    }

    protected JavaMatrix cloneMatrix() {
        JavaMatrix jm=new JavaMatrix(this.row,this.column);
        jm.data=Arrays.copyOf(this.data,this.data.length);
        jm.isSquare=this.isSquare;
        jm.isIdentical=this.isIdentical;
        jm.isDiagonal=this.isDiagonal;
        jm.isZeroMatrix=this.isZeroMatrix;
        jm.nonOneNumberMain=this.nonOneNumberMain;
        jm.nonZeroNumberMain=this.nonZeroNumberMain;
        jm.nonZeroNumber=this.nonZeroNumber;
        jm.nonZeroNumberNotMain=this.nonZeroNumberNotMain;
        return jm;
    }
}
