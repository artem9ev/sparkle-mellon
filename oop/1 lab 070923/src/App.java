import java.util.*;

public class App 
{
    static Scanner sr = new Scanner(System.in);

    public static int InputInt(String s)
    {
        System.out.print(s);
        return sr.nextInt();
    }
    public static boolean isProstoe(int x)
    {
        if(x < 2){
            return false;
        }
        for(int i = 2; i < x; i++){
            if (x % i == 0){
                return false;
            }
        }
        return true;
    }
    public static boolean isSymmetric(int[] a){
        for(int i = 0; i < a.length / 2; i++){
            if(a[i] != a[a.length - 1 - i]){
                return false;
            }
        }
        return true;
    }
    public static boolean isSoversh(int x){
        int c = 0;
        for(int i = 0; i < x; i++){
            if (x % i == 0){
                c += i;
            }
        }
        return c == x;
    }

    public static void main(String[] args) throws Exception
    {
        int n = InputInt("Input array size: ");
        int countProstie = 0;
        int countSoversh = 0;

        int[] a = new int[n];
        for(int i = 0; i < n; i++)
        {
            a[i] = InputInt("a[" + i + "] = ");
        }
        for (int i = 0; i < n; i++)
        {
            if(isProstoe(a[i])){
                countProstie++;
            }
        }
        for (int i = 0; i < n; i++){
            if (isSoversh(a[i])){
                countSoversh++;
            }
        }

        System.out.printf("answer = %d", countProstie);
        System.out.println();

        System.out.printf(isSymmetric(a) ? "Симметриен" : "Не симметричен");
    }
}
