// Press Shift twice to open the Search Everywhere dialog and type `show whitespaces`,
// then press Enter. You can now see whitespace characters in your code.
public class Main {
    public static void main(String[] args) {
        PassengerShip pasShip = new PassengerShip("Lagoon", -3, 9, 19, 400, 80);
        Ship practiceTarget1 = new Ship("target1", 10, 7, 0);
        Ship practiceTarget2 = new Ship("target2", -10, 7, 0);
        Warship warship = new Warship("Cascad", 6, 8, 30, 6, 7);

        pasShip.print();
        practiceTarget1.print();
        practiceTarget2.print();
        warship.print();

        System.out.println("Can hit target1: " + warship.canHit(practiceTarget1.getCoordinate()));
        System.out.println("Can hit target2: " + warship.canHit(practiceTarget2.getCoordinate()));
    }
}