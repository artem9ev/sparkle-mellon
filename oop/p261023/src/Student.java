public class Student implements Entity
{
    private String fio;
    private String adress;
    private String fakultet;
    private int kurs;
    private int[] mark;
    private Stats stats;
    Student(String fio, String adress, String fakultet, int kurs, int[] mark,
            int strength, int agility, int intellegene){
        this.fio = fio;
        this.adress = adress;
        this.fakultet = fakultet;
        this.kurs = kurs;
        this.mark = mark;
        stats = new Stats(strength, agility, intellegene);
    }
    public double SredBal(){
        double s = 0;
        for (int m : mark){
            s += m;
        }
        return s;
    }
    public Stats getStats(){
        return stats;
    }
    public void DealDamage(){
        
    }
}
