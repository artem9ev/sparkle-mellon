import java.util.Scanner;

public class Main {
    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);
        System.out.print("Введите рубли: ");
        int r = sc.nextInt();
        System.out.print("Введите копейки: ");
        int k = sc.nextInt();

        Money m = new Money(r, k);
        m.print();
    }
}