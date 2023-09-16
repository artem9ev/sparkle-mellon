import java.util.Random;

public class Matrix {
    private int[][] matrix;
    private int s = 0;
    Matrix(int size, int start, int end){
        Random rand = new Random();
        s = size;
        matrix = new int[s][s];
        for (int i = 0; i < s; i++){
            for (int k = 0; k < s; k++){
                matrix[i][k] = rand.nextInt(start, end);
            }
        }
    }
    public int sumProst(){
        int s = 0;
        for (int i = 0; i < s; i++){
            for (int k = 0; k < s; k++){
                if (k > i && Mathf.isProstoe(matrix[i][k])){
                    s += matrix[i][k];
                }
            }
        }
        return s;
    }
    public int multyplyElems(int a){
        int p = 1;
        for (int i = 0; i < s; i++){
            for (int k = 0; k < s; k++){
                if ((i + k + 1) > s && matrix[i][k] > a){
                    p *= matrix[i][k];
                }
            }
        }
        return p;
    }
    public int multyplySoversh(){
        int p = 1;
        for (int i = 0; i < s; i++){
            for (int k = 0; k < s; k++){
                if (Mathf.isSoversh(matrix[i][k])){
                    p *= matrix[i][k];
                }
            }
        }
        return p;
    }
    public void changeEven(){
        for (int i = 0; i < s; i++){
            int c = 0;
            for (int k = 0; k < s; k++){
                if (Mathf.isSoversh(matrix[i][k])){
                    c++;
                }
            }
            if (c > 2){
                for (int k = 0; k < s; k++){
                    if (matrix[i][k] % 2 == 0){
                        matrix[i][k] = 0;
                    }
                }
            }
        }
    }
    public void print(){
        for (int i = 0; i < s; i++){
            for (int k = 0; k < s; k++){
                System.out.print(matrix[i][k] + "\t");
            }
            System.out.println();
        }
    }
}
