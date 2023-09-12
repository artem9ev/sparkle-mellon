import java.util.Scanner;

public class Main
{
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Введите кол-во: ");
        int n = sc.nextInt();

        Massive m = new Massive(n);
        m.print();
        int sum = m.sum();

        System.out.print("Сумма эл-ов " + sum);
        System.out.print(m.isSymmetric() ? "Массив симметричен" : "Массив не симметричен");
    }
}