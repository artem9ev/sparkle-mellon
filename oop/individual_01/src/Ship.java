public class Ship {
    private String name;
    private Coordinate coordinate;
    private int speed;
    public Ship(String name, int x, int y, int speed) {
        this.name = name;
        this.coordinate = new Coordinate(x, y);
        this.speed = speed;
    }

    public void setName(String name) {
        this.name = name;
    }
    public void setCoordinate(int x, int y) {
        this.coordinate.setX(x);
        this.coordinate.setY(y);
    }
    public void setSpeed(int speed) {
        this.speed = speed;
    }

    public Coordinate getCoordinate() {
        return coordinate;
    }

    public void print(){
        System.out.println("Корабль: " + name + "\nКоордината: " + coordinate.getX() + " " +coordinate.getY()
        + "\nСкорость: " + speed + "\n");
    }
}
