import java.util.Scanner;

public class Main {
    private static Scanner sc;
    private static String getNewLine(String x){
        System.out.print(x);
        return sc.nextLine();
    }
    private static int getNewInt(String x){
        System.out.print(x);
        return sc.nextInt();
    }
    private static double getNewDouble(String x){
        System.out.print(x);
        return sc.nextDouble();
    }

    public static void main(String[] args) {
        sc = new Scanner(System.in);
        System.out.println("Ввод данных автомобиля: ");
        String marka = getNewLine("Введите марку: ");
        String number = getNewLine("Ввелите номер: ");
        String vin = getNewLine("Введите вин: ");
        int year = getNewInt("Введите год выпуска: ");
        double vol = getNewDouble("Введите объем двигателя: ");
        int price = getNewInt("Введите цену: ");
        int km = getNewInt("Введите пробег: ");
        Avto a = new Avto(marka, number, vin, year, vol, price, km);
        System.out.println("Данные авто:\n" + a.toString());

        String g = sc.nextLine();
        String f = getNewLine("Введите ФИО водителя: ");
        int pricekm = getNewInt("Введите стоимость за километр: ");
        Taxi t = new Taxi(marka, number, vin, year, vol, price, km, f, pricekm);
        double km1 = getNewDouble("Введите дальность расстояния в км: ");
        System.out.println("Стоимость поездки: " + t.stoim(km1));
        System.out.println("Данные такси:\n" + t.toString());
    }
}