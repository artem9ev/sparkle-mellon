import java.util.Scanner;

public class Main {
    private static int getInt(String str){
        Scanner sc = new Scanner(System.in);
        System.out.println(str);
        int x = sc.nextInt();
        return x;
    }

    public static void main(String[] args) {
        int d = getInt("Введите день: ");
        int m = getInt("Введите месяц: ");
        int y = getInt("Введите год: ");
        try {
            Data date = new Data(d, m, y);
        }
        catch (MyException e) {
            System.out.println(e.getMessage() + e.getDate());
        }
    }
}