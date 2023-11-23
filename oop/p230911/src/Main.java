import java.util.Scanner;

public class Main
{
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Введите кол-во: ");
        int n = sc.nextInt();

        Massive m1 = new Massive(n);

        System.out.print("Введите кол-во: ");
        n = sc.nextInt();
        int[] mas = new int[n];
        System.out.print("Введите эл-ты: ");
        for (int i = 0; i < n; i++){
            mas[i] = sc.nextInt();       }
        Massive m2 = new Massive(mas);

        m1.print();
        m2.print();
        int sum1 = m1.sum();
        int sum2 = m2.sum();

        System.out.println("Сумма эл-ов1 " + sum1);
        System.out.println("Сумма эл-ов2 " + sum2);
        System.out.println(m1.isSymmetric() ? "Массив 1 симметричен" : "Массив 1 не симметричен");
        System.out.println(m2.isSymmetric() ? "Массив 2 симметричен" : "Массив 2 не симметричен");
        System.out.println("Сумма простых эл-ов1 " + m1.sumProstie());
        System.out.println("Сумма простых эл-ов2 " + m2.sumProstie());

    }
}