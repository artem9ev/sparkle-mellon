import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Matrix m = new Matrix(6, 6, 10);
        // 1
        m.print();
        System.out.println("Сумма простых: " + m.sumProst());
        // 3
        Scanner in = new Scanner(System.in);
        System.out.print("Введите a: ");
        int a = in.nextInt();
        System.out.println("Произведение эл-ов > a, лежащих ниже побочной: " + m.multyplyElems(a));
        // 4
        System.out.println("Произведение совершенных эл-ов: " + m.multyplySoversh());
        // 2
        System.out.println("Замена четных при двух совершенных в строке: ");
        m.changeEven();
        m.print();
    }
}