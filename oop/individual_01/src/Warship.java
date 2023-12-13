public class Warship extends Ship{
    private int numOfGuns;
    private int attackRange;

    public Warship(String name, int x, int y, int speed, int numOfGuns, int attackRange) {
        super(name, x, y, speed);
        this.numOfGuns = numOfGuns;
        this.attackRange = attackRange;
    }
    public boolean canHit(Coordinate coord){
        int xDiff = getCoordinate().getX() - coord.getX();
        int yDiff = getCoordinate().getY() - coord.getY();
        return attackRange >= Math.sqrt(xDiff * xDiff + yDiff * yDiff);
    }
    public boolean canHit(int x, int y){
        int xDiff = getCoordinate().getX() - x;
        int yDiff = getCoordinate().getY() - y;
        return attackRange <= Math.sqrt(xDiff * xDiff + yDiff * yDiff);
    }
    public void print(){
        super.print();
        System.out.println("Кол-во орудий: " + numOfGuns + "\nДальность поражения: " + attackRange + "\n");
    }
}
