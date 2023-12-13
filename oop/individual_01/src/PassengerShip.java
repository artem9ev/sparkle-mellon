public class PassengerShip extends Ship{
    private int numOfSeats;
    private int numOfBoats;
    public PassengerShip(String name, int x, int y, int speed, int numOfSeats, int numOfBoats) {
        super(name, x, y, speed);
        this.numOfSeats = numOfSeats;
        this.numOfBoats = numOfBoats;
    }
    public int CountSurviving(){
        return numOfSeats;
    }
    public void print(){
        super.print();
        System.out.println("Кол-во мест: " + numOfSeats + "\nКол-во шлюпок: " + numOfBoats + "\n");
    }
}
