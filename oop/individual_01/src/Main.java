import java.util.*;
public class Main {
    public static void main(String[] args) {

        Spisok spisok = new Spisok();
        spisok.addAdressP(new AdressPoshta("MIRA", "MOSKOW", "RUSSIA", "89342"));
        spisok.addAdressP(new AdressPoshta("MIRA1", "MOSKOW1", "RUSSIA1", "75904"));
        spisok.addAdressP(new AdressPoshta("MIRA2", "MOSKOW2", "RUSSIA2", "32466"));


        // Поиск записи по признаку
        AdressPoshta foundRecord = spisok.searchCountryObject("RUSSIA");
        System.out.println();
        System.out.println("Найденная запись: " + foundRecord.toString());
        System.out.println();

        // Удаление записи
        System.out.println("delete of adress poshta");
        spisok.removeAdressPoshta(foundRecord);

        // Сортировка записей по названию
        System.out.println("Сортировка по country:");
        spisok.sortByCountry();
        spisok.print();

        // Сортировка записей по стране
        System.out.println("Сортировка по city:");
        spisok.sortByCity();
        spisok.print();

        // Сортировка записей по широте
        System.out.println("Сортировка по street:");
        spisok.sortByStreet();
        spisok.print();

        // Сортировка записей по долготе
        System.out.println("Сортировка по posta code:");
        spisok.sortByPostaCode();
        spisok.print();
    }
}

